/**
   @file token.cpp
   @brief It contains the definitions of the functions on token.h

   @author Bruno da Silva Belo
 */

#include "token.h"

uc::Token::Token(kind_t _token, std::string const& _lexval, unsigned _row,
                 unsigned _col)
    : lexval(std::move(_lexval)), row(_row), col(_col), token(_token) {}

std::string uc::Token::to_string() const {
  std::string out = "[";
  out += std::to_string(row) + ", " + std::to_string(col) + ", " +
         get_type(token) + ", " + lexval + "]";

  return out;
}

bool uc::Token::has_ended() const { return token == kind_t::fe; }

std::pair<unsigned, unsigned> uc::Token::get_position() const {
  return std::pair<unsigned, unsigned>(row, col);
}

uc::kind_t uc::Token::get_kind() const { return token; }

std::string uc::get_type(kind_t const token) {
  switch (token) {
  case kind_t::id_t:
    return std::string("id_t");
  case kind_t::int_t:
    return std::string("int_t");
  case kind_t::int_l:
    return std::string("int_l");
  case kind_t::float_t:
    return std::string("float_t");
  case kind_t::float_l:
    return std::string("float_l");
  case kind_t::string_t:
    return std::string("string_t");
  case kind_t::string_l:
    return std::string("string_l");
  case kind_t::vector_t:
    return std::string("vector_t");
  case kind_t::void_t:
    return std::string("void_t");
  case kind_t::add_o:
    return std::string("add_o");
  case kind_t::mult_o:
    return std::string("mult_o");
  case kind_t::inv_o:
    return std::string("inv_o");
  case kind_t::r_o:
    return std::string("r_o");
  case kind_t::re_o:
    return std::string("re_o");
  case kind_t::atr_o:
    return std::string("atr_o");
  case kind_t::and_o:
    return std::string("and_o");
  case kind_t::or_o:
    return std::string("or_o");
  case kind_t::neg_o:
    return std::string("neg_o");
  case kind_t::if_c:
    return std::string("if_c");
  case kind_t::else_c:
    return std::string("else_c");
  case kind_t::while_c:
    return std::string("while_c");
  case kind_t::for_c:
    return std::string("for_c");
  case kind_t::open_paren:
    return std::string("open_paren");
  case kind_t::close_paren:
    return std::string("close_paren");
  case kind_t::open_brace:
    return std::string("open_brace");
  case kind_t::close_brace:
    return std::string("close_brace");
  case kind_t::semicolon:
    return std::string("semicolon");
  case kind_t::colon:
    return std::string("colon");
  case kind_t::quotation:
    return std::string("quotation");
  case kind_t::dot:
    return std::string("dot");
  case kind_t::comma:
    return std::string("comma");
  case kind_t::return_c:
    return std::string("return_c");
  case kind_t::fe:
    return std::string("File's End");
  case kind_t::error:
    return std::string("error");
  }
}
