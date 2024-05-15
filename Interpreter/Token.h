#pragma once
#include <any>
#include <string>
#include <utility>
#include "TokenType.h"

class Token {
public:
  const TokenType type;
  const std::string lexeme;
  const std::any literal;
  const int line;
  Token(TokenType type, std::string lexeme, std::any literal, int line);
  std::string toString() const;
};
