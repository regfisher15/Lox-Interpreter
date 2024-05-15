#pragma once

#include <any>
#include <cassert>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include "Expr.h"

class AstPrinter: public ExprVisitor {
public:
  std::string print(std::shared_ptr<Expr> expr);
  std::any visitBinaryExpr(std::shared_ptr<Binary> expr) override;
  std::any visitGroupingExpr(std::shared_ptr<Grouping> expr) override;
  std::any visitLiteralExpr(std::shared_ptr<Literal> expr) override;
  std::any visitUnaryExpr(std::shared_ptr<Unary> expr) override;
private:
  template <class... E>
  std::string parenthesize(std::string_view name, E... expr){
    assert((... && std::is_same_v<E, std::shared_ptr<Expr>>));
    std::ostringstream builder;
    builder << "(" << name;
    ((builder << " " << print(expr)), ...);
    builder << ")";
    return builder.str();
  }
};
