/**
   @file test.cpp
   @brief It contains the test of the ucc

   @author Bruno da Silva Belo
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "token.h"
#include <string>

TEST_CASE("Testing the type's tokens", "[token]") {
  SECTION("Testing human case readness") {
    REQUIRE("Char" == uc::get_type(uc::kind_t::CHAR));
    REQUIRE("Int" == uc::get_type(uc::kind_t::INT));
    REQUIRE("Float" == uc::get_type(uc::kind_t::FLOAT));
    REQUIRE("String" == uc::get_type(uc::kind_t::STRING));
    REQUIRE("Error" == uc::get_type(uc::kind_t::ERROR));
    REQUIRE("Identifier" == uc::get_type(uc::kind_t::IDENTIFIER));
    REQUIRE("Int Literal" == uc::get_type(uc::kind_t::INT_LITERAL));
    REQUIRE("Char Literal" == uc::get_type(uc::kind_t::CHAR_LITERAL));
    REQUIRE("Float Literal" == uc::get_type(uc::kind_t::FLOAT_LITERAL));
    REQUIRE("String Literal" == uc::get_type(uc::kind_t::STRING_LITERAL));
    REQUIRE("Add Operator" == uc::get_type(uc::kind_t::ADD_OPERATOR));
    REQUIRE("Mult Operator" == uc::get_type(uc::kind_t::MULT_OPERATOR));
    REQUIRE("Rel Operator" == uc::get_type(uc::kind_t::REL_OPERATOR));
    REQUIRE("Atr Operator" == uc::get_type(uc::kind_t::ATR_OPERATOR));
    REQUIRE("If Word" == uc::get_type(uc::kind_t::IF));
    REQUIRE("Else Word" == uc::get_type(uc::kind_t::ELSE));
    REQUIRE("While Word" == uc::get_type(uc::kind_t::WHILE));
    REQUIRE("For Word" == uc::get_type(uc::kind_t::FOR));
    REQUIRE("File's End" == uc::get_type(uc::kind_t::FE));
  }
}

TEST_CASE("Testing the return of the lexer", "[lexer]") {
  SECTION("Testing one token per input") {}
}
