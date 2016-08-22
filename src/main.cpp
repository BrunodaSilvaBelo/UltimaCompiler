/**
   @mainpage Ultima Compiler
   @brief A compiler to pass in compiler course.

   The front-end of the compiler, verifying if the parameters is right and the
   format of the file is usable.
   Always use clang-format.
   @author Bruno da Silva Belo
   @see https://github.com/isocpp/CppCoreGuidelines
   @see http://llvm.org/docs/tutorial/LangImpl1.html
   @see http://clang.llvm.org/docs/ClangFormat.html
*/
#include "gsl/gsl_assert.h"
#include "lexer.h"
#include "token.h"
#include "util.h"
#include <algorithm>
#include <stdio.h>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  Expects(argc >= 2);

  uc::Lexer lexer(argv[1]);
  if (!lexer.is_ready()) {
    fprintf(stderr, "Error while opening the source code!\n");
    return -1;
  }

  auto t = lexer.nextToken();
  std::vector<uc::Token> tokens;
  while (!t.has_ended()) {
    tokens.push_back(t);
    t = lexer.nextToken();
  }

  auto s = uc::show_token_to_alcino(std::move(tokens));

  printf("%s\n", s.c_str());

  return 0;
}
