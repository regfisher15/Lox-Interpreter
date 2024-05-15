#include "RuntimeError.h"
RuntimeError::RuntimeError(const Token& token, std::string_view message) 
: std::runtime_error{message.data()}, token{token} {}