#include "lexer.h"
#include <algorithm>
#include <cctype>
#include <stdio.h>

namespace {
constexpr char COMMENT = '#';
}

uc::Lexer::Lexer(std::string const& source) : code(std::move(source)) {}

bool uc::Lexer::is_ready() const { return code.is_open(); }

uc::Token uc::Lexer::get_next_token() {
  static auto next_character = [this]() {
    ++col;
    return static_cast<char>(code.get());
  };

  static char last_char = next_character();

  // Ignored caracteres
  while (isspace(last_char)) {
    if (last_char == '\n') {
      ++row;
      col = 0;
    }
    last_char = next_character();
  }

  // Names
  if (isalpha(last_char) || last_char == '_') {
    std::string lexval = std::string(1, last_char);
    last_char          = next_character();

    while (isalnum(last_char) || last_char == '_') {
      lexval += last_char;
      last_char = next_character();
    }

    if (lexval == "int")
      return get_token(uc::kind_t::int_t, std::move(lexval));
    if (lexval == "float")
      return get_token(uc::kind_t::float_t, std::move(lexval));
    if (lexval == "string")
      return get_token(uc::kind_t::string_t, std::move(lexval));
    if (lexval == "void")
      return get_token(uc::kind_t::void_t, std::move(lexval));
    if (lexval == "while")
      return get_token(uc::kind_t::while_c, std::move(lexval));
    if (lexval == "if")
      return get_token(uc::kind_t::if_c, std::move(lexval));
    if (lexval == "else")
      return get_token(uc::kind_t::else_c, std::move(lexval));
    if (lexval == "for")
      return get_token(uc::kind_t::for_c, std::move(lexval));
    if (lexval == "return")
      return get_token(uc::kind_t::return_c, std::move(lexval));

    return get_token(uc::kind_t::id_t, std::move(lexval));
  }

  // Numbers
  if (isdigit(last_char)) {
    std::string lexval = std::string(1, last_char);
    while (isdigit(last_char = next_character()))
      lexval += last_char;

    if (last_char == '.') {
      lexval += last_char;
      while (isdigit(last_char = next_character()))
        lexval += last_char;

      return get_token(uc::kind_t::float_l, std::move(lexval));
    }

    return get_token(uc::kind_t::int_l, std::move(lexval));
  }

  // strings
  if (last_char == '"') {
    std::string lexval = std::string(1, last_char);
    while ((last_char = next_character()) != '"') {
      if (last_char == EOF) {
        return get_token(uc::kind_t::quotation, std::move(lexval));
      }

      if (last_char != '\n') {
        lexval += last_char;
        continue;
      }

      auto token = get_token(uc::kind_t::error, std::move(lexval));
      ++row;
      col       = 0;
      last_char = next_character();
      return token;
    }

    lexval += last_char;
    last_char = next_character();
    return get_token(uc::kind_t::string_l, std::move(lexval));
  }

  // = or ==
  if (last_char == '=') {
    std::string lexval = std::string(1, last_char);
    last_char          = next_character();

    if (last_char == '=') {
      lexval += last_char;
      last_char = next_character();
    }

    return get_token(uc::kind_t::atr_o, std::move(lexval));
  }

  // < ,<=, > or >=
  if ((last_char == '<') || (last_char == '>')) {
    std::string lexval = std::string(1, last_char);
    last_char          = next_character();

    if (last_char == '=') {
      lexval += last_char;
      last_char = next_character();
    }

    return get_token(uc::kind_t::r_o, std::move(lexval));
  }

  // Comentaries
  if (last_char == COMMENT) {
    do {
      last_char = next_character();
    } while (last_char != EOF && last_char != '\n');

    if (last_char != EOF)
      return get_next_token();
  }

  // EOF
  if (last_char == EOF)
    return get_token(uc::kind_t::fe, "");

  auto one_char              = last_char;
  last_char                  = next_character();
  static auto one_char_token = [this](char& character) {
    if (character == '+' || character == '-')
      return get_token(uc::kind_t::add_o, std::string(1, character));
    if (character == '*' || character == '/' || character == '%')
      return get_token(uc::kind_t::mult_o, std::string(1, character));
    if (character == 169)
      return get_token(uc::kind_t::neg_o, std::string(1, 169));
    if (character == '~')
      return get_token(uc::kind_t::inv_o, std::string(1, character));
    if (character == '{')
      return get_token(uc::kind_t::open_brace, std::string(1, character));
    if (character == '}')
      return get_token(uc::kind_t::close_brace, std::string(1, character));
    if (character == '(')
      return get_token(uc::kind_t::open_paren, std::string(1, character));
    if (character == ')')
      return get_token(uc::kind_t::close_paren, std::string(1, character));
    if (character == ';')
      return get_token(uc::kind_t::semicolon, std::string(1, character));
    if (character == ':')
      return get_token(uc::kind_t::colon, std::string(1, character));
    if (character == ',')
      return get_token(uc::kind_t::comma, std::string(1, character));
    if (character == '|')
      return get_token(uc::kind_t::or_o, std::string(1, character));
    if (character == '&')
      return get_token(uc::kind_t::and_o, std::string(1, character));

    return get_token(uc::kind_t::error, std::string(1, character));
  };

  return one_char_token(one_char);
}

uc::Token uc::Lexer::get_token(uc::kind_t token,
                               std::string const& lexval) const {
  unsigned size = lexval.size();
  return uc::Token(token, std::move(lexval), row, col - size);
}
