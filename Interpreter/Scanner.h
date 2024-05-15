#pragma once
#include <map>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include "ErrorFile.h"
#include "Token.h"

class Scanner {
  static const std::map<std::string, TokenType> keywords;
  std::string_view source;
  std::vector<Token> tokens;
  int start = 0;
  int current = 0;
  int line = 1;

public:
  Scanner(std::string_view source);
  std::vector<Token> scanTokens();

private:
  void scanToken();
  void identifier();
  void number();
  void string();
  bool match(char expected);
  char peek();
  char peekNext();
  bool isAlpha(char c);
  bool isAlphaNumeric(char c);
  bool isDigit(char c);
  bool isAtEnd();
  char advance();
  void addToken(TokenType type);
  void addToken(TokenType type, std::any literal);
};
