#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <fstream>
#include <string>

namespace uc {
class Lexer {
public:
  explicit Lexer(std::string const& source);
  bool is_ready() const;
  Token get_next_token();

private:
  std::fstream code;
  unsigned row = 1;
  unsigned col = 0;

  Token get_token(kind_t token, std::string const& lexema) const;
};
} // namespace uc

#endif /* LEXER_H */
