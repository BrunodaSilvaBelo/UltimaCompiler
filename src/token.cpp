#include "token.h"
#include <utility>

using Token = token::Token;

Token::Token(kind _token, std::string _text, unsigned _row, unsigned _col)
    : text(std::move(_text)), row(_row), col(_col), token(_token) {}

std::string Token::to_string() const {
  std::string out = "[";
  out += text + ", " + std::to_string(row) + ", " + std::to_string(col) + ", " +
         get_type(token) + "]";

  return out;
}

bool Token::has_ended() const {
  return token == kind::FE;
}

std::string token::get_type(kind const token) {
  std::string type;

  switch (token) {
  case kind::IDENTIFIER:
    type = "Identifier";
    break;
  case kind::INT:
    type = "Int";
    break;
  case kind::CHAR:
    type = "Char";
    break;
  case kind::FLOAT:
    type = "Float";
    break;
  case kind::STRING:
    type = "String";
    break;
  case kind::INTLITERAL:
    type = "Int Literal";
    break;
  case kind::CHARLITERAL:
    type = "Char Literal";
    break;
  case kind::FLOATLITERAL:
    type = "Float Literal";
    break;
  case kind::STRINGLITERAL:
    type = "String Literal";
    break;
  case kind::ADDOPERATOR:
    type = "Add Operator";
    break;
  case kind::ATROPERATOR:
    type = "Atr Operator";
    break;
  case kind::MULTOPERATOR:
    type = "Mult Operator";
    break;
  case kind::RELOPERATOR:
    type = "Rel Operator";
    break;
  case kind::IF:
    type = "If Word";
    break;
  case kind::WHILE:
    type = "While Word";
    break;
  case kind::FOR:
    type = "For Word";
    break;
  case kind::ELSE:
    type = "Else Word";
    break;
  case kind::FE:
    type = "File's End";
    break;
  case kind::END:
    type = "End of the Lexer";
    break;
  case kind::ERROR:
    type = "Error";
    break;
  }

  return type;
}
