#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "token.h"

using namespace std;

TEST_CASE("Testing the type's tokens", "[token]") {
  REQUIRE("Char" == token::get_type(token::kind::CHAR));
  REQUIRE("Int" == token::get_type(token::kind::INT));
  REQUIRE("Float" == token::get_type(token::kind::FLOAT));
  REQUIRE("String" == token::get_type(token::kind::STRING));
  REQUIRE("Error" == token::get_type(token::kind::ERROR));
  REQUIRE("Identifier" == token::get_type(token::kind::IDENTIFIER));
  REQUIRE("Int Literal" == token::get_type(token::kind::INTLITERAL));
  REQUIRE("Char Literal" == token::get_type(token::kind::CHARLITERAL));
  REQUIRE("Float Literal" == token::get_type(token::kind::FLOATLITERAL));
  REQUIRE("String Literal" == token::get_type(token::kind::STRINGLITERAL));
  REQUIRE("Add Operator" == token::get_type(token::kind::ADDOPERATOR));
  REQUIRE("Rel Operator" == token::get_type(token::kind::RELOPERATOR));
  REQUIRE("Atr Operator" == token::get_type(token::kind::ATROPERATOR));
  REQUIRE("If Word" == token::get_type(token::kind::IF));
  REQUIRE("Else Word" == token::get_type(token::kind::ELSE));
  REQUIRE("While Word" == token::get_type(token::kind::WHILE));
  REQUIRE("For Word" == token::get_type(token::kind::FOR));
  REQUIRE("File's End" == token::get_type(token::kind::FE));
  REQUIRE("End of the Lexer" == token::get_type(token::kind::END));
}
