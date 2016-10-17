#include "syntax.h"
#include "token.h"
#include <array>
#include <cstdint>
#include <fstream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace {
std::map<uint8_t, std::map<uint8_t, uint8_t>> table;
std::array<std::pair<uc::not_term, std::string>, 31> const terminals = {
    {std::make_pair(uc::not_term::Program, "Program"),
     std::make_pair(uc::not_term::Program1, "Program1"),
     std::make_pair(uc::not_term::Program2, "Program2"),
     std::make_pair(uc::not_term::DecParamList, "DecParamList"),
     std::make_pair(uc::not_term::DecParamList1, "DecParamList1"),
     std::make_pair(uc::not_term::Statement, "Statement"),
     std::make_pair(uc::not_term::Statement1, "Statement1"),
     std::make_pair(uc::not_term::Statement2, "Statement2"),
     std::make_pair(uc::not_term::Statement3, "Statement3"),
     std::make_pair(uc::not_term::Else, "Else"),
     std::make_pair(uc::not_term::AtrSt, "AtrSt"),
     std::make_pair(uc::not_term::RValue, "RValue"),
     std::make_pair(uc::not_term::RValue1, "RValue1"),
     std::make_pair(uc::not_term::CallParamList, "CallParamList"),
     std::make_pair(uc::not_term::CallParamList1, "CallParamList1"),
     std::make_pair(uc::not_term::LogExp, "LogExp"),
     std::make_pair(uc::not_term::LogExp1, "LogExp1"),
     std::make_pair(uc::not_term::LogExp2, "LogExp2"),
     std::make_pair(uc::not_term::RelExp, "RelExp"),
     std::make_pair(uc::not_term::RelExp1, "RelExp1"),
     std::make_pair(uc::not_term::RelExp2, "RelExp2"),
     std::make_pair(uc::not_term::RelExp3, "RelExp3"),
     std::make_pair(uc::not_term::AriExp, "AriExp"),
     std::make_pair(uc::not_term::AriExp1, "AriExp1"),
     std::make_pair(uc::not_term::AriExp2, "AriExp2"),
     std::make_pair(uc::not_term::AriExp3, "AriExp3"),
     std::make_pair(uc::not_term::AriExp4, "AriExp4"),
     std::make_pair(uc::not_term::ParenAriExp, "ParenAriExp"),
     std::make_pair(uc::not_term::Type, "Type"),
     std::make_pair(uc::not_term::Opn, "Opn"),
     std::make_pair(uc::not_term::Empty, "$")}};

struct type_stack {
public:
  std::string type;
};

struct not_term_stack : public type_stack {
public:
  uc::not_term nt;

  not_term_stack(std::string const& _type, uc::not_term _nt) {
    type = std::move(_type);
    nt   = _nt;
  }
};

struct term_stack : public type_stack {
public:
  uc::kind_t t;

  term_stack(std::string const& _type, uc::kind_t _t) {
    type = std::move(_type);
    t    = std::move(_t);
  }
};

type_stack* create_type_stack(uc::not_term nt) {
  return new not_term_stack("nt", nt);
}

type_stack* create_type_stack(uc::kind_t k) {
  return new term_stack("t", std::move(k));
}

template <typename T> std::vector<type_stack*> foo(T const& t) {
  return std::vector<type_stack*>(std::move(t));
}

template <std::size_t I = 0, typename Vec, typename Tup>
typename std::enable_if<I == std::tuple_size<Tup>::value,
                        std::vector<type_stack*>>::type
add_to_vector(Vec& v, Tup& t) {
  return v;
}

template <std::size_t I = 0, typename Vec, typename Tup>
    typename std::enable_if <
    I<std::tuple_size<Tup>::value, std::vector<type_stack*>>::type
    add_to_vector(Vec& v, Tup& t) {
  v.push_back(create_type_stack(std::get<I>(t)));
  return add_to_vector<I + 1>(v, t);
}

template <typename... T> std::vector<type_stack*> vector_derivation(T... args) {
  auto arg_tuple = std::make_tuple(args...);

  std::vector<type_stack*> v;
  add_to_vector(v, arg_tuple);

  return v;
}

std::array<std::vector<type_stack*>, 75> const derivation = {
    {vector_derivation(uc::not_term::Type, uc::not_term::Program1),
     vector_derivation(uc::kind_t::void_t, uc::not_term::Program2),
     vector_derivation(
         uc::kind_t::id_t, uc::kind_t::open_paren, uc::not_term::DecParamList,
         uc::kind_t::close_paren, uc::kind_t::open_brace,
         uc::not_term::Statement, uc::kind_t::return_c, uc::not_term::Opn,
         uc::kind_t::semicolon, uc::kind_t::close_brace, uc::not_term::Program),
     vector_derivation(uc::kind_t::main_c, uc::kind_t::open_paren,
                       uc::not_term::DecParamList, uc::kind_t::close_paren,
                       uc::kind_t::open_brace, uc::not_term::Statement,
                       uc::kind_t::return_c, uc::not_term::Opn,
                       uc::kind_t::semicolon, uc::kind_t::close_brace),
     vector_derivation(uc::kind_t::id_t, uc::kind_t::open_paren,
                       uc::not_term::DecParamList, uc::kind_t::close_paren,
                       uc::kind_t::open_brace, uc::not_term::Statement,
                       uc::kind_t::close_brace, uc::not_term::Program),
     vector_derivation(uc::kind_t::main_c, uc::kind_t::open_paren,
                       uc::not_term::DecParamList, uc::kind_t::close_paren,
                       uc::kind_t::open_brace, uc::not_term::Statement,
                       uc::kind_t::close_brace),
     vector_derivation(uc::not_term::Type, uc::kind_t::id_t,
                       uc::not_term::DecParamList1),
     vector_derivation(uc::not_term::Empty),
     vector_derivation(uc::kind_t::comma, uc::not_term::DecParamList),
     vector_derivation(uc::not_term::Empty),
     vector_derivation(uc::kind_t::if_c, uc::kind_t::open_paren,
                       uc::not_term::LogExp, uc::kind_t::close_paren,
                       uc::kind_t::open_brace, uc::not_term::Statement,
                       uc::kind_t::close_brace, uc::not_term::Else),
     vector_derivation(uc::kind_t::while_c, uc::kind_t::open_paren,
                       uc::not_term::LogExp, uc::kind_t::close_paren,
                       uc::kind_t::open_brace, uc::not_term::Statement,
                       uc::kind_t::close_brace, uc::not_term::Statement),
     vector_derivation(uc::kind_t::for_c, uc::kind_t::open_paren,
                       uc::not_term::AtrSt, uc::kind_t::semicolon,
                       uc::not_term::Opn, uc::kind_t::semicolon,
                       uc::not_term::Opn, uc::kind_t::close_paren,
                       uc::kind_t::open_brace, uc::not_term::Statement,
                       uc::kind_t::close_brace, uc::not_term::Statement),
     vector_derivation(uc::kind_t::int_t, uc::kind_t::id_t,
                       uc::not_term::Statement1),
     vector_derivation(uc::kind_t::float_t, uc::kind_t::id_t,
                       uc::not_term::Statement1),
     vector_derivation(uc::kind_t::string_t, uc::kind_t::id_t,
                       uc::not_term::Statement1),
     vector_derivation(uc::kind_t::bool_t, uc::kind_t::id_t,
                       uc::not_term::Statement1),
     vector_derivation(uc::kind_t::vector_t, uc::not_term::Statement3),
     vector_derivation(uc::kind_t::id_t, uc::not_term::Statement2),
     vector_derivation(uc::not_term::Empty),
     vector_derivation(uc::kind_t::semicolon, uc::not_term::Statement),
     vector_derivation(uc::kind_t::atr_o, uc::not_term::RValue,
                       uc::kind_t::semicolon, uc::not_term::Statement),
     vector_derivation(uc::kind_t::atr_o, uc::not_term::RValue,
                       uc::kind_t::semicolon, uc::not_term::Statement),
     vector_derivation(uc::kind_t::open_paren, uc::not_term::CallParamList,
                       uc::kind_t::close_paren, uc::kind_t::semicolon,
                       uc::not_term::Statement),
     vector_derivation(uc::kind_t::id_t, uc::not_term::Statement1),
     vector_derivation(uc::not_term::Type, uc::kind_t::id_t, uc::kind_t::colon,
                       uc::not_term::Opn, uc::kind_t::semicolon,
                       uc::not_term::Statement),
     vector_derivation(uc::kind_t::else_c, uc::kind_t::open_brace,
                       uc::not_term::Statement, uc::kind_t::close_brace,
                       uc::not_term::Statement),
     vector_derivation(uc::not_term::Statement),
     vector_derivation(uc::not_term::Type, uc::kind_t::id_t, uc::kind_t::atr_o,
                       uc::not_term::RValue),
     vector_derivation(uc::kind_t::id_t, uc::kind_t::atr_o,
                       uc::not_term::RValue1),
     vector_derivation(uc::kind_t::id_t, uc::not_term::RValue1),
     vector_derivation(uc::kind_t::neg_o, uc::not_term::RelExp,
                       uc::not_term::LogExp2),
     vector_derivation(uc::kind_t::inv_o, uc::not_term::ParenAriExp,
                       uc::not_term::AriExp4, uc::not_term::AriExp3,
                       uc::not_term::RelExp3, uc::not_term::RelExp2,
                       uc::not_term::LogExp2),
     vector_derivation(uc::kind_t::open_paren, uc::not_term::LogExp,
                       uc::kind_t::close_paren, uc::not_term::AriExp4,
                       uc::not_term::AriExp3, uc::not_term::RelExp3,
                       uc::not_term::RelExp2, uc::not_term::LogExp2),
     vector_derivation(uc::kind_t::int_l, uc::not_term::AriExp4,
                       uc::not_term::AriExp3, uc::not_term::RelExp3,
                       uc::not_term::RelExp2, uc::not_term::LogExp2),

     vector_derivation(uc::kind_t::bool_l, uc::not_term::AriExp4,
                       uc::not_term::AriExp3, uc::not_term::RelExp3,
                       uc::not_term::RelExp2, uc::not_term::LogExp2),
     vector_derivation(uc::kind_t::string_l, uc::not_term::AriExp4,
                       uc::not_term::AriExp3, uc::not_term::RelExp3,
                       uc::not_term::RelExp2, uc::not_term::LogExp2),
     vector_derivation(uc::kind_t::open_paren, uc::not_term::CallParamList,
                       uc::kind_t::close_paren),
     vector_derivation(uc::not_term::AriExp4, uc::not_term::AriExp3,
                       uc::not_term::RelExp3, uc::not_term::RelExp2,
                       uc::not_term::LogExp2),
     vector_derivation(uc::not_term::LogExp, uc::not_term::CallParamList1),
     vector_derivation(uc::kind_t::comma, uc::not_term::CallParamList),
     vector_derivation(uc::not_term::Empty),
     vector_derivation(uc::not_term::LogExp1, uc::not_term::LogExp2),
     vector_derivation(uc::kind_t::neg_o, uc::not_term::RelExp),
     vector_derivation(uc::not_term::RelExp),
     vector_derivation(uc::kind_t::and_o, uc::not_term::LogExp1,
                       uc::not_term::LogExp2),
     vector_derivation(uc::kind_t::or_o, uc::not_term::LogExp1,
                       uc::not_term::LogExp2),
     vector_derivation(uc::not_term::Empty),
     vector_derivation(uc::not_term::RelExp1, uc::not_term::RelExp2),
     vector_derivation(uc::not_term::AriExp, uc::not_term::RelExp3),
     vector_derivation(uc::kind_t::re_o, uc::not_term::RelExp1),
     vector_derivation(uc::not_term::Empty),
     vector_derivation(uc::kind_t::r_o, uc::not_term::AriExp),
     vector_derivation(uc::not_term::Empty),
     vector_derivation(uc::not_term::AriExp1, uc::not_term::AriExp3),
     vector_derivation(uc::not_term::AriExp2, uc::not_term::AriExp4),
     vector_derivation(uc::kind_t::inv_o, uc::not_term::ParenAriExp),
     vector_derivation(uc::not_term::ParenAriExp),
     vector_derivation(uc::kind_t::add_o, uc::not_term::AriExp1,
                       uc::not_term::AriExp3),
     vector_derivation(uc::not_term::Empty),
     vector_derivation(uc::kind_t::mult_o, uc::not_term::AriExp2,
                       uc::not_term::AriExp4),
     vector_derivation(uc::not_term::Empty),
     vector_derivation(uc::kind_t::open_paren, uc::not_term::LogExp,
                       uc::kind_t::close_paren),
     vector_derivation(uc::not_term::Opn), vector_derivation(uc::kind_t::int_t),
     vector_derivation(uc::kind_t::float_t),
     vector_derivation(uc::kind_t::string_t),
     vector_derivation(uc::kind_t::bool_t),
     vector_derivation(uc::kind_t::vector_t),
     vector_derivation(uc::kind_t::id_t), vector_derivation(uc::kind_t::int_l),
     vector_derivation(uc::kind_t::bool_l),
     vector_derivation(uc::kind_t::string_l),
     vector_derivation(uc::kind_t::float_l),
     vector_derivation(uc::kind_t::float_l, uc::not_term::AriExp4,
                       uc::not_term::AriExp3, uc::not_term::RelExp3,
                       uc::not_term::RelExp2, uc::not_term::LogExp2)}};
} // namespace

uc::Syntax::Syntax(std::string const& source, std::string const& conf_file)
    : lexer(std::move(source)) {
  if (!lexer.is_ready()) {
    fprintf(stderr, "Error while opening the source code!\n");
    abort();
  }
  configure(std::move(conf_file));
}

uc::actions uc::Syntax::process(uc::Token const& input) {
  auto action                             = actions::derive;
  static std::vector<type_stack*> m_stack = {
      create_type_stack(uc::not_term::Program)};

  auto term = m_stack.back();
  m_stack.pop_back();

  if (term->type == "t") {
    auto token = ((term_stack*)term);
    if (token->t != input.get_kind()) {
      printf("Token nao eh o esperado!\n");
      abort();
    }

    return uc::actions::read_input;
  }

  std::string alcino_output =
      uc::get_not_terminal(static_cast<not_term_stack*>(term)->nt) + " -> ";

  auto nt = ((not_term_stack*)term)->nt;
  if (nt == uc::not_term::Empty)
    return action;

  auto x = std::underlying_type<uc::not_term>::type(nt);
  auto y = std::underlying_type<uc::kind_t>::type(input.get_kind());

  auto search = table.find(x);
  if (search == table.end()) {
    printf("Nao-terminal nao encontrado!\n");
    abort();
  }

  auto search1 = search->second.find(y);
  if (search1 == search->second.end()) {
    printf("Producao inexistente!\n");
    abort();
  }

  for (int i = derivation[search1->second].size() - 1; i >= 0; --i)
    m_stack.push_back(derivation[search1->second][i]);

  auto id = true;
  for (auto& i : derivation[search1->second]) {
    if (i->type == "nt")
      alcino_output += uc::get_not_terminal(((not_term_stack*)i)->nt);
    else {
      alcino_output += "\"" + uc::get_type(((term_stack*)i)->t) + "\"";
      if (id) {
        id       = false;
        auto tok = input.get_kind();
        if (tok == uc::kind_t::add_o || tok == uc::kind_t::mult_o ||
            tok == uc::kind_t::id_t || tok == uc::kind_t::int_l ||
            tok == uc::kind_t::bool_l || tok == uc::kind_t::string_l ||
            tok == uc::kind_t::float_l || tok == uc::kind_t::r_o ||
            tok == uc::kind_t::re_o)
          alcino_output += "(" + input.get_lexval() + ")";
      }
    }
    alcino_output += " ";
  }

  printf("%s\n", alcino_output.c_str());

  return action;
}

void uc::Syntax::run() {
  auto t = lexer.nextToken();
  std::vector<uc::Token> tokens;
  while (!t.has_ended()) {
    auto action = process(t);
    if (action == uc::actions::read_input)
      t = lexer.nextToken();
  }
}

void uc::Syntax::configure(std::string const& conf_file) const {
  std::fstream conf(std::move(conf_file));

  std::array<int, 3> terms;

  while (conf.good()) {
    conf >> terms[0] >> terms[1] >> terms[2];
    table[terms[0]][terms[1]] = terms[2];
  }
}

std::string uc::get_not_terminal(uc::not_term nt) {
  return terminals[std::underlying_type<uc::not_term>::type(nt)].second;
}
