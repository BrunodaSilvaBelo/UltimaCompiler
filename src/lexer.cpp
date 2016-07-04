#include "lexer.h"
#include <algorithm>
#include <cctype>
#include <stdio.h>

namespace {
struct characters {
  static constexpr char COMMENT = '#';
};
}

uc::Lexer::Lexer(std::string source) : code(std::move(source)) {}

bool uc::Lexer::is_ready() const { return code.is_open(); }

uc::Token uc::Lexer::get_next_token() {
  static auto next_character = [this]() {
    ++col;
    return static_cast<char>(code.get());
  };

  static char last_char = next_character();

  while (isspace(last_char)) {
    if (last_char == '\n') {
      ++row;
      col = 0;
    }
    last_char = next_character();
  }

  if (isalpha(last_char) || last_char == '_') {
    std::string lexema = std::string(1, last_char);
    last_char          = next_character();

    while (isalnum(last_char) || last_char == '_') {
      lexema += last_char;
      last_char = next_character();
    }

    if (lexema == "int")
      return get_token(uc::kind_t::INT, std::move(lexema));
    else if (lexema == "char")
      return get_token(uc::kind_t::CHAR, std::move(lexema));
    else if (lexema == "float")
      return get_token(uc::kind_t::FLOAT, std::move(lexema));
    else if (lexema == "string")
      return get_token(uc::kind_t::STRING, std::move(lexema));
    else if (lexema == "while")
      return get_token(uc::kind_t::WHILE, std::move(lexema));
    else if (lexema == "if")
      return get_token(uc::kind_t::IF, std::move(lexema));
    else if (lexema == "else")
      return get_token(uc::kind_t::ELSE, std::move(lexema));
    else if (lexema == "for")
      return get_token(uc::kind_t::FOR, std::move(lexema));

    return get_token(uc::kind_t::IDENTIFIER, std::move(lexema));
  }

  if (isdigit(last_char)) {
    std::string lexema = std::string(1, last_char);
    while (isdigit(last_char = next_character()))
      lexema += last_char;

    if (last_char == '.') {
      lexema += last_char;
      while (isdigit(last_char = next_character()))
        lexema += last_char;

      return get_token(uc::kind_t::FLOAT_LITERAL, std::move(lexema));
    }

    return get_token(uc::kind_t::INT_LITERAL, std::move(lexema));
  }

  if (last_char == '=') {
    std::string lexema = std::string(1, last_char);
    last_char          = next_character();

    return get_token(uc::kind_t::ATR_OPERATOR, std::move(lexema));
  }

  if (last_char == characters::COMMENT) {
    do {
      last_char = next_character();
    } while (last_char != EOF && last_char != '\n');

    if (last_char != EOF)
      return get_next_token();
  }

  if (last_char == EOF)
    return get_token(uc::kind_t::FE, "");

  auto one_char              = last_char;
  last_char                  = next_character();
  static auto one_char_token = [this](char& character) {
    if (character == '+' || character == '-')
      return get_token(uc::kind_t::ADD_OPERATOR, std::string(1, character));
    if (character == '*' || character == '/' || character == '%')
      return get_token(uc::kind_t::MULT_OPERATOR, std::string(1, character));

    return get_token(uc::kind_t::ERROR, std::string(1, character));
  };
  return one_char_token(one_char);
}

uc::Token uc::Lexer::get_token(uc::kind_t token, std::string lexema) const {
  return uc::Token(token, lexema, row,
                   col - static_cast<unsigned>(lexema.size()));
}
