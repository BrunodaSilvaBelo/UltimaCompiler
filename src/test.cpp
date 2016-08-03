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
    REQUIRE("int_t" == uc::get_type(uc::kind_t::int_t));
    REQUIRE("float_t" == uc::get_type(uc::kind_t::float_t));
    REQUIRE("string_t" == uc::get_type(uc::kind_t::string_t));
    REQUIRE("error" == uc::get_type(uc::kind_t::error));
    REQUIRE("id_t" == uc::get_type(uc::kind_t::id_t));
    REQUIRE("int_l" == uc::get_type(uc::kind_t::int_l));
    REQUIRE("float_l" == uc::get_type(uc::kind_t::float_l));
    REQUIRE("string_l" == uc::get_type(uc::kind_t::string_l));
    REQUIRE("add_o" == uc::get_type(uc::kind_t::add_o));
    REQUIRE("mult_o" == uc::get_type(uc::kind_t::mult_o));
    REQUIRE("r_o" == uc::get_type(uc::kind_t::r_o));
    REQUIRE("atr_o" == uc::get_type(uc::kind_t::atr_o));
    REQUIRE("if_c" == uc::get_type(uc::kind_t::if_c));
    REQUIRE("else_c" == uc::get_type(uc::kind_t::else_c));
    REQUIRE("while_c" == uc::get_type(uc::kind_t::while_c));
    REQUIRE("for_c" == uc::get_type(uc::kind_t::for_c));
    REQUIRE("File's End" == uc::get_type(uc::kind_t::fe));
  }
}

TEST_CASE("Testing the return of the lexer", "[lexer]") {
  SECTION("Testing one token per input") {}
}
