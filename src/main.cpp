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
#include "syntax.h"
#include <string>

namespace {
const std::string conf_file = "../src/syntax.conf";
}

int main(int argc, char** argv) {
  Expects(argc >= 2);

  uc::Syntax syn(argv[1], conf_file);
  syn.run();

  return 0;
}
