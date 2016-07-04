/**
   @file token.cpp
   @brief It contains the definitions of the functions on token.h

   @author Bruno da Silva Belo
 */

#include "token.h"

uc::Token::Token(kind_t _token, std::string _text, unsigned _row, unsigned _col)
    : text(std::move(_text)), row(_row), col(_col), token(_token) {}

std::string uc::Token::to_string() const {
  std::string out = "[";
  out += text + ", " + std::to_string(row) + ", " + std::to_string(col) + ", " +
         get_type(token) + "]";

  return out;
}

bool uc::Token::has_ended() const { return token == kind_t::FE; }

std::pair<unsigned, unsigned> uc::Token::get_position() const {
  return std::pair<unsigned, unsigned>(row, col);
}

uc::kind_t uc::Token::get_kind() const { return token; }

std::string uc::get_type(kind_t const token) {
  std::string type;

  switch (token) {
  case kind_t::IDENTIFIER:
    type = "Identifier";
    break;
  case kind_t::INT:
    type = "Int";
    break;
  case kind_t::CHAR:
    type = "Char";
    break;
  case kind_t::FLOAT:
    type = "Float";
    break;
  case kind_t::STRING:
    type = "String";
    break;
  case kind_t::INT_LITERAL:
    type = "Int Literal";
    break;
  case kind_t::CHAR_LITERAL:
    type = "Char Literal";
    break;
  case kind_t::FLOAT_LITERAL:
    type = "Float Literal";
    break;
  case kind_t::STRING_LITERAL:
    type = "String Literal";
    break;
  case kind_t::ADD_OPERATOR:
    type = "Add Operator";
    break;
  case kind_t::ATR_OPERATOR:
    type = "Atr Operator";
    break;
  case kind_t::MULT_OPERATOR:
    type = "Mult Operator";
    break;
  case kind_t::REL_OPERATOR:
    type = "Rel Operator";
    break;
  case kind_t::IF:
    type = "If Word";
    break;
  case kind_t::WHILE:
    type = "While Word";
    break;
  case kind_t::FOR:
    type = "For Word";
    break;
  case kind_t::ELSE:
    type = "Else Word";
    break;
  case kind_t::FE:
    type = "File's End";
    break;
  case kind_t::ERROR:
    type = "Error";
    break;
  }

  return type;
}
