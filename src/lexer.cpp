#include "lexer.h"
#include <cctype>
#include <regex>
#include <utility>

lexer::Lexer::Lexer(std::string source) : code(std::move(source)) {}

bool lexer::Lexer::is_ready() const { return code.is_open(); }

token::Token lexer::Lexer::get_next_token() {
  static char last_char = next_character();

  while (isspace(last_char)) {
    if (last_char == '\n') {
      ++col;
      row = 0;
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
      return get_token(token::kind::INT, std::move(lexema));
    else if (lexema == "char")
      return get_token(token::kind::CHAR, std::move(lexema));
    else if (lexema == "float")
      return get_token(token::kind::FLOAT, std::move(lexema));
    else if (lexema == "string")
      return get_token(token::kind::STRING, std::move(lexema));
    else if (lexema == "while")
      return get_token(token::kind::WHILE, std::move(lexema));
    else if (lexema == "if")
      return get_token(token::kind::IF, std::move(lexema));
    else if (lexema == "else")
      return get_token(token::kind::ELSE, std::move(lexema));
    else if (lexema == "for")
      return get_token(token::kind::FOR, std::move(lexema));

    return get_token(token::kind::IDENTIFIER, std::move(lexema));
  }

  if (isdigit(last_char)) {
    std::string lexema = std::string(1, last_char);
    while (isdigit(last_char = next_character()))
      lexema += last_char;

    if (last_char == '.') {
      lexema += last_char;
      while (isdigit(last_char = next_character()))
        lexema += last_char;

      return get_token(token::kind::FLOATLITERAL, std::move(lexema));
    }

    if (isalpha(last_char))
      return get_token(token::kind::ERROR, std::move(lexema));

    return get_token(token::kind::INTLITERAL, std::move(lexema));
  }

  if (last_char == EOF)
    return get_token(token::kind::FE, "");

  last_char = next_character();
  return token::Token(token::kind::END, "", row, col);
}

char lexer::Lexer::next_character() {
  char character = static_cast<char>(code.get());
  ++row;

  return character;
}

token::Token lexer::Lexer::get_token(token::kind token,
                                     std::string lexema) const {
  return token::Token(token, std::move(lexema),
                      row - static_cast<unsigned>(lexema.size()), col);
}
