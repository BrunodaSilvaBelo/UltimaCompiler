/**
   @mainpage Ultima Compiler
   @brief A compiler to pass in compiler course.
   Always use clang-format.
   @author Bruno da Silva Belo
   @see https://github.com/isocpp/CppCoreGuidelines
   @see http://llvm.org/docs/tutorial/LangImpl1.html
*/
#include "lexer.h"
#include "token.h"
#include <gsl/gsl.h>
#include <stdio.h>
#include <string>
#include <fstream>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("ucc source_code.uc\n");
    return -1;
  }

  lexer::Lexer lexer(argv[1]);
  if (!lexer.is_ready()) {
    printf("Error while opening the source code!\n");
    return -1;
  }

  auto t = lexer.get_next_token();
  while (!t.has_ended()) {
    printf("%s\n", t.to_string().c_str());
    t = lexer.get_next_token();
  }

  return 0;
}
