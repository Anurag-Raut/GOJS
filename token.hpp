

#ifndef TOKEN_H
#define TOKEN_H

#include <any>
#include <optional>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
using namespace std;
enum TokenType {
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SEMICOLON,
  SLASH,
  STAR,
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,
  IDENTIFIER,
  STRING,
  NUMBER,
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUNC,
  FOR,
  IF,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,
  ENDOFFILE
};

std::unordered_map<std::string, TokenType> KEYWORDS = {
    {"and", TokenType::AND},       {"class", TokenType::CLASS},
    {"else", TokenType::ELSE},     {"false", TokenType::FALSE},
    {"func", TokenType::FUNC},       {"for", TokenType::FOR},
    {"if", TokenType::IF},         {"nil", TokenType::NIL},
    {"or", TokenType::OR},         {"print", TokenType::PRINT},
    {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
    {"this", TokenType::THIS},     {"true", TokenType::TRUE},
    {"var", TokenType::VAR},       {"while", TokenType::WHILE}};

class Literal {
 public:
  any value;

  Literal( string s) : value(s) {}
  Literal(double d) : value(d) {}
  Literal(bool b) : value(b) {}
  Literal() : value(nullopt) {}

  void printLiteral() {
    if (value.type() == typeid(string)) {
      cout << any_cast<string>(value) << endl;
    } else if (value.type() == typeid(double)) {
      cout << any_cast<double>(value) << endl;
    } else if (value.type() == typeid(bool)) {
      cout << any_cast<bool>(value) << endl;
    } else {
      cout << "Unknown type" << endl;
    }
  }

  

};

class Token {
 public:
  TokenType type;
  string lexeme;
  Literal literal;
  int line;

  Token(TokenType type, string lexeme, Literal literal, int line) {
    this->type = type;
    this->lexeme = lexeme;
    this->literal = literal;
    this->line = line;
  }

  Token() = default;
};
#endif