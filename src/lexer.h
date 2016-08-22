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
  Token nextToken();

private:
  std::fstream code;
  unsigned row = 1;
  unsigned col = 0;

  Token get_token(kind_t token, std::string const& lexval) const;
};
} // namespace uc

#endif /* LEXER_H */
