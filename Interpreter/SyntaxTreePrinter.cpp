#include "SyntaxTreePrinter.h"

std::string AstPrinter::print(std::shared_ptr<Expr> expr) {
    return std::any_cast<std::string>(expr->accept(*this));
}
std::any AstPrinter::visitBinaryExpr(std::shared_ptr<Binary> expr) {
    return parenthesize(expr->op.lexeme, expr->left, expr->right);
}
std::any AstPrinter::visitGroupingExpr(std::shared_ptr<Grouping> expr) {
    return parenthesize("group", expr->expression);
}
std::any AstPrinter::visitLiteralExpr(std::shared_ptr<Literal> expr) {
    auto& value_type = expr->value.type();
    if (value_type == typeid(nullptr)) {
      return "nil";
    } else if (value_type == typeid(std::string)) {
      return std::any_cast<std::string>(expr->value);
    } else if (value_type == typeid(double)) {
      return std::to_string(std::any_cast<double>(expr->value));
    } else if (value_type == typeid(bool)) {
      return std::any_cast<bool>(expr->value) ? "true" : "false";
    }
    return "Error in visitLiteralExpr: literal type not recognized.";
}
std::any AstPrinter::visitUnaryExpr(std::shared_ptr<Unary> expr) {
    return parenthesize(expr->op.lexeme, expr->right);
}