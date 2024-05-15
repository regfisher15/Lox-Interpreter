#pragma once
#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include "ErrorFile.h"
#include "Expr.h"
#include "Stmt.h"
#include "Token.h"
#include "TokenType.h"

class Parser {
  struct ParseError: public std::runtime_error {
    using std::runtime_error::runtime_error;
  };
  const std::vector<Token>& tokens;
  int current = 0;

public:
  Parser(const std::vector<Token>& tokens);
  std::vector<std::shared_ptr<Stmt>> parse();

private:
  std::shared_ptr<Expr> expression();
  std::shared_ptr<Stmt> declaration();
  std::shared_ptr<Stmt> classDeclaration();
  std::shared_ptr<Stmt> statement();
  std::shared_ptr<Stmt> forStatement();
  std::shared_ptr<Stmt> ifStatement();
  std::shared_ptr<Stmt> printStatement();
  std::shared_ptr<Stmt> returnStatement();
  std::shared_ptr<Stmt> varDeclaration();
  std::shared_ptr<Stmt> whileStatement();
  std::shared_ptr<Stmt> expressionStatement();
  std::shared_ptr<Function> function(std::string kind);
  std::vector<std::shared_ptr<Stmt>> block();
  std::shared_ptr<Expr> assignment();
  std::shared_ptr<Expr> orExpression();
  std::shared_ptr<Expr> andExpression();
  std::shared_ptr<Expr> equality();
  std::shared_ptr<Expr> comparison();
  std::shared_ptr<Expr> term();
  std::shared_ptr<Expr> factor();
  std::shared_ptr<Expr> unary();
  std::shared_ptr<Expr> finishCall(std::shared_ptr<Expr> callee);
  std::shared_ptr<Expr> call();
  std::shared_ptr<Expr> primary();
  Token consume(TokenType type, std::string_view message);
  bool check(TokenType type);
  Token advance();
  bool isAtEnd();
  Token peek();
  Token previous();
  void synchronize();

  template <class... T>
  bool match(T... type) {
    assert((... && std::is_same_v<T, TokenType>));
    if ((... || check(type))) {
      advance();
      return true;
    }
    return false;
  }
  ParseError error(const Token& token, std::string_view message) {
    ::error(token, message);
    return ParseError{""};
  }  
};