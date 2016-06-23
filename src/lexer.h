#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <fstream>
#include <string>

namespace lexer {
class Lexer {
public:
  Lexer(std::string source);
  bool is_ready() const;
  token::Token get_next_token();

private:
  std::fstream code;
  unsigned row = 0;
  unsigned col = 0;

  char next_character();
  token::Token get_token(token::kind token, std::string lexema) const;
};
}

#endif /* LEXER_H */
