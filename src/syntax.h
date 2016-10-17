#ifndef ULTIMA_SYNTAX_H
#define ULTIMA_SYNTAX_H

#include "lexer.h"
#include <string>

namespace uc {
enum class not_term : size_t {
  Program,
  Program1,
  Program2,
  DecParamList,
  DecParamList1,
  Statement,
  Statement1,
  Statement2,
  Statement3,
  Else,
  AtrSt,
  RValue,
  RValue1,
  CallParamList,
  CallParamList1,
  LogExp,
  LogExp1,
  LogExp2,
  RelExp,
  RelExp1,
  RelExp2,
  RelExp3,
  AriExp,
  AriExp1,
  AriExp2,
  AriExp3,
  AriExp4,
  ParenAriExp,
  Type,
  Opn,
  Empty
};

enum class actions { read_input, derive };

class Token;

class Syntax {
public:
  Syntax(std::string const& source, std::string const& table);
  actions process(Token const& input);
  void run();

private:
  Lexer lexer;
  void configure(std::string const& conf_file) const;
};

std::string get_not_terminal(not_term nt);
} // namespace uc

#endif /* ULTIMA_SYNTAX_H */
