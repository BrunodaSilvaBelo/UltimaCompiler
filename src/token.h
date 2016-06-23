/**
   @file token.h
   It have the types of the language as well functions associated with it, and
   the Token class.

   @brief It contains the types, and Tokens classes.
   @author Bruno da Silva Belo
*/
#ifndef TOKEN_H
#define TOKEN_H

#include <cstdint>
#include <string>

namespace token {

enum class kind : uint8_t {
  INT = 0x0,
  INTLITERAL,
  CHAR,
  CHARLITERAL,
  FLOAT,
  FLOATLITERAL,
  STRING,
  STRINGLITERAL,
  IDENTIFIER,
  ADDOPERATOR,
  MULTOPERATOR,
  RELOPERATOR,
  ATROPERATOR,
  IF,
  ELSE,
  FOR,
  WHILE,
  FE,
  END,
  ERROR = 0xff
};

/**
   @class Token
   @brief The token class.
*/
class Token {
public:
  /**
     @brief The default constructor.
     @param _token The type of the token.
     @param _text The name of the type.
     @param _row The row that token is.
     @param _col The column that token is.
  */
  Token(kind _token, std::string _text, unsigned _row, unsigned _col);
  /**
     @brief It can print the class.
     @return std::string A string with the contents of the token.
  */
  std::string to_string() const;
  bool has_ended() const;

private:
  std::string text;
  unsigned row;
  unsigned col;
  kind token;
};

/**
   @brief Returns a string with the type's name.
   @param token The token that want it the type.
   @return A string with the type's name.
*/
std::string get_type(kind const token);
}

#endif /* TOKEN_H */
