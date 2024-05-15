#pragma once
#include <any>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include "ErrorFile.h"
#include "Token.h"

class Environment: public std::enable_shared_from_this<Environment>
{
  friend class Interpreter;
  std::shared_ptr<Environment> enclosing;
  std::map<std::string, std::any> values;

public:
  Environment();
  Environment(std::shared_ptr<Environment> enclosing);
  std::any get(const Token& name);
  void assign(const Token& name, std::any value);
  void define(const std::string& name, std::any value);
  std::shared_ptr<Environment> ancestor(int distance);
  std::any getAt(int distance, const std::string& name);
  void assignAt(int distance, const Token& name, std::any value);
};
