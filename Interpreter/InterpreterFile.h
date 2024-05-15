#pragma once
#include <any>
#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <utility>
#include "Environment.h"
#include "ErrorFile.h"
#include "Expr.h"
#include "CallableFile.h"
#include "ClassFile.h"
#include "FunctionFile.h"
#include "InstanceFile.h"
#include "ReturnFile.h"
#include "RuntimeError.h"
#include "Stmt.h"

class NativeClock: public LoxCallable {
public:
  int arity() override;
  std::any call(Interpreter& interpreter, std::vector<std::any> arguments) override;
  std::string toString() override;
};

class Interpreter: public ExprVisitor, public StmtVisitor 
{
friend class LoxFunction;
public:  std::shared_ptr<Environment> globals{new Environment};
private:
  std::shared_ptr<Environment> environment = globals;
  std::map<std::shared_ptr<Expr>, int> locals;
  std::any evaluate(std::shared_ptr<Expr> expr);
  void execute(std::shared_ptr<Stmt> stmt);
  void executeBlock(const std::vector<std::shared_ptr<Stmt>>& statements, std::shared_ptr<Environment> environment);
  std::any lookUpVariable(const Token& name, std::shared_ptr<Expr> expr);
  void checkNumberOperand(const Token& op, const std::any& operand);
  void checkNumberOperands(const Token& op, const std::any& left, const std::any& right);
  bool isTruthy(const std::any& object);
  bool isEqual(const std::any& a, const std::any& b);
  std::string stringify(const std::any& object);

public:
  Interpreter();
  void interpret(const std::vector<std::shared_ptr<Stmt>>& statements);
  void resolve(std::shared_ptr<Expr> expr, int depth);
  std::any visitBlockStmt(std::shared_ptr<Block> stmt) override;
  std::any visitClassStmt(std::shared_ptr<Class> stmt) override;
  std::any visitExpressionStmt(std::shared_ptr<Expression> stmt) override;
  std::any visitFunctionStmt(std::shared_ptr<Function> stmt) override;
  std::any visitIfStmt(std::shared_ptr<If> stmt) override;
  std::any visitPrintStmt(std::shared_ptr<Print> stmt) override;
  std::any visitReturnStmt(std::shared_ptr<Return> stmt) override;
  std::any visitVarStmt(std::shared_ptr<Var> stmt) override;
  std::any visitWhileStmt(std::shared_ptr<While> stmt) override;
  std::any visitAssignExpr(std::shared_ptr<Assign> expr) override;
  std::any visitBinaryExpr(std::shared_ptr<Binary> expr) override;
  std::any visitCallExpr(std::shared_ptr<Call> expr) override;
  std::any visitGetExpr(std::shared_ptr<Get> expr) override;
  std::any visitGroupingExpr(std::shared_ptr<Grouping> expr) override;
  std::any visitLiteralExpr(std::shared_ptr<Literal> expr) override;
  std::any visitLogicalExpr(std::shared_ptr<Logical> expr) override;
  std::any visitSetExpr(std::shared_ptr<Set> expr) override;
  std::any visitSuperExpr(std::shared_ptr<Super> expr) override;
  std::any visitThisExpr(std::shared_ptr<This> expr) override;
  std::any visitUnaryExpr(std::shared_ptr<Unary> expr) override;
  std::any visitVariableExpr(std::shared_ptr<Variable> expr) override;
};
