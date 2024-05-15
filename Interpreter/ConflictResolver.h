#pragma once
#include <functional>
#include <map>
#include <memory>
#include <vector>
#include "InterpreterFile.h"

class Resolver: public ExprVisitor, public StmtVisitor {
  Interpreter& interpreter;
  std::vector<std::map<std::string, bool>> scopes;
  enum class FunctionType {
    NONE,
    FUNCTION,
    INITIALIZER,
    METHOD
  };
  FunctionType currentFunction = FunctionType::NONE;

private:
  enum class ClassType {
    NONE,
    CLASS,
    SUBCLASS
  };
  ClassType currentClass = ClassType::NONE;
  void resolve(std::shared_ptr<Stmt> stmt);
  void resolve(std::shared_ptr<Expr> expr);
  void resolveFunction(std::shared_ptr<Function> function, FunctionType type);
  void beginScope();
  void endScope();
  void declare(const Token& name);
  void define(const Token& name);
  void resolveLocal(std::shared_ptr<Expr> expr, const Token& name);

public:
  Resolver(Interpreter& interpreter);
  void resolve(const std::vector<std::shared_ptr<Stmt>>& statements);
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
