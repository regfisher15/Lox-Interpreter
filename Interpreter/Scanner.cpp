#include "Scanner.h"

Scanner::Scanner(std::string_view source) : source {source} {}
std::vector<Token> Scanner::scanTokens() {
    while (!isAtEnd()) {
      start = current;
      scanToken();
    }
    tokens.emplace_back(END_OF_FILE, "", nullptr, line);
    return tokens;
}
void Scanner::scanToken() {
    char c = advance();
    switch (c) {
      case '(': addToken(LEFT_PAREN); break;
      case ')': addToken(RIGHT_PAREN); break;
      case '{': addToken(LEFT_BRACE); break;
      case '}': addToken(RIGHT_BRACE); break;
      case ',': addToken(COMMA); break;
      case '.': addToken(DOT); break;
      case '-': addToken(MINUS); break;
      case '+': addToken(PLUS); break;
      case ';': addToken(SEMICOLON); break;
      case '*': addToken(STAR); break;
      case '!':
        addToken(match('=') ? BANG_EQUAL : BANG);
        break;
      case '=':
        addToken(match('=') ? EQUAL_EQUAL : EQUAL);
        break;
      case '<':
        addToken(match('=') ? LESS_EQUAL : LESS);
        break;
      case '>':
        addToken(match('=') ? GREATER_EQUAL : GREATER);
        break;
      case '/':
        if (match('/')) {
          while (peek() != '\n' && !isAtEnd()) advance();
        } else {
          addToken(SLASH);
        }
        break;
      case ' ':
      case '\r':
      case '\t':
        break;
      case '\n':
        ++line;
        break;
      case '"': string(); break;
      default:
        if (isDigit(c)) {
          number();
        } else if (isAlpha(c)) {
          identifier();
        } else {
          error(line, "Unexpected character.");
        }
        break;
    };
}
void Scanner::identifier() {
    while (isAlphaNumeric(peek())) advance();
    std::string text = std::string{source.substr(start, current - start)};
    TokenType type;
    auto match = keywords.find(text);
    if (match == keywords.end()) {
      type = IDENTIFIER;
    } else {
      type = match->second;
    }
    addToken(type);
}
void Scanner::number() {
    while (isDigit(peek())) advance();
    if (peek() == '.' && isDigit(peekNext())) {
      advance();
      while (isDigit(peek())) advance();
    }
    addToken(NUMBER, std::stod(std::string{source.substr(start, current - start)}));
}
void Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
      if (peek() == '\n') ++line;
      advance();
    }
    if (isAtEnd()) {
      error(line, "Unterminated string.");
      return;
    }
    advance();
    std::string value{source.substr(start + 1, current - 2 - start)};
    addToken(STRING, value);
}
bool Scanner::match(char expected) {
    if (isAtEnd()) return false;
    if (source[current] != expected) return false;
    ++current;
    return true;
}
char Scanner::peek() {
    if (isAtEnd()) return '\0';
    return source[current];
}
char Scanner::peekNext() {
    if (current + 1 >= source.length()) return '\0';
    return source[current + 1];
}
bool Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
bool Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}
bool Scanner::isDigit(char c) {
    return c >= '0' && c <= '9';
}
bool Scanner::isAtEnd() {
    return current >= source.length();
}
char Scanner::advance() {
    return source[current++];
}
void Scanner::addToken(TokenType type) {
    addToken(type, nullptr);
}
void Scanner::addToken(TokenType type, std::any literal) {
    std::string text{source.substr(start, current - start)};
    tokens.emplace_back(type, std::move(text), std::move(literal), line);
}
const std::map<std::string, TokenType> Scanner::keywords = {
  {"and",    TokenType::AND},
  {"class",  TokenType::CLASS},
  {"else",   TokenType::ELSE},
  {"false",  TokenType::FALSE},
  {"for",    TokenType::FOR},
  {"fun",    TokenType::FUN},
  {"if",     TokenType::IF},
  {"nil",    TokenType::NIL},
  {"or",     TokenType::OR},
  {"print",  TokenType::PRINT},
  {"return", TokenType::RETURN},
  {"super",  TokenType::SUPER},
  {"this",   TokenType::THIS},
  {"true",   TokenType::TRUE},
  {"var",    TokenType::VAR},
  {"while",  TokenType::WHILE},
};
