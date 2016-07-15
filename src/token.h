/**
   @file token.h
   It have the types of the language as well functions associated with it, and
   the Token class.

   @brief It contains the types, and Tokens classes.
   @author Bruno da Silva Belo
*/
#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <utility>

namespace uc {
enum class kind_t : uint8_t {
  INT = 0x0,
  INT_LITERAL,
  CHAR,
  CHAR_LITERAL,
  FLOAT,
  FLOAT_LITERAL,
  STRING,
  STRING_LITERAL,
  IDENTIFIER,
  ADD_OPERATOR,
  MULT_OPERATOR,
  REL_OPERATOR,
  ATR_OPERATOR,
  IF,
  ELSE,
  FOR,
  WHILE,
  FE,
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
  Token(kind_t _token, std::string const& _text, unsigned _row, unsigned _col);
  /**
     @brief It can print the class.
     @return std::string A string with the contents of the token.
  */
  std::string to_string() const;
  /**
     @brief It returns true if it is the final state token.
     @return bool false if it has token to be read, true otherwise.
   */
  bool has_ended() const;

  std::pair<unsigned, unsigned> get_position() const;

  kind_t get_kind() const;

private:
  std::string text;
  unsigned row;
  unsigned col;
  kind_t token;
};

/**
   @brief Returns a string with the type's name.
   @param token The token that want it the type.
   @return A string with the type's name.
*/
std::string get_type(kind_t const token);
} // namespace uc

#endif /* TOKEN_H */
