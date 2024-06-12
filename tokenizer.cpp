

#include <optional>
#include <unordered_map>
#include <variant>
#include <vector>

#include "token.hpp"
#include "utils.hpp"

using namespace std;

class Tokenizer {
 public:
  vector<Token> tokens;
  string source;
  Tokenizer(string source) {
    this->source = source;

    while (!isAtEnd()) {
      start = current;
      scanToken();
    }

    tokens.push_back(Token(TokenType::ENDOFFILE, "", Literal(), line));
  }

  void display() {
    for (int i = 0; i < tokens.size(); i++) {
      cout << " TokenType: " << tokens[i].type
           << " TokenLexeme: " << tokens[i].lexeme << " TokenLiternal: ";
      // if (tokens[i].literal.value.has_value()) {
      tokens[i].literal.printLiteral();

      cout << endl;
    }
  }

 private:
  int start = 0, current = 0;
  int line = 1;

  bool isAtEnd() { return current >= source.size(); }

  void addToken(TokenType type, Literal literal) {
    string text = source.substr(start, current - start);
    // cout<<text<<endl;
    tokens.push_back(Token(type, text, literal, line));
  }
  void addToken(TokenType type, Literal literal, string lexeme) {
    // cout<<text<<endl;

    tokens.push_back(Token(type, lexeme, literal, line));
  }
  void addToken(TokenType type) { addToken(type, Literal()); }

  bool match(char expected) {
    if (isAtEnd()) {
      return false;
    }

    if (source[current] != expected) {
      return false;
    }

    current++;
    return 1;
  }

  char peek() {
    if (isAtEnd()) return '\0';
    return source[current];
  }

  void stringTokenize() {
    while (peek() != '"' && !isAtEnd()) {
      if (peek() == '\n') {
        line++;
      }
      current++;
    }
    if (peek() != '"') {
      reportError("unclosed string", line);
    }
    start++;

    //  current--;
    string text = source.substr(start, current - start);
    current++;
    addToken(TokenType::STRING, Literal(text), text);
  }
  void tokenizedigit() {
    int numberOfDecimals = 0;
    while ((isdigit(peek()) || peek() == '.') && !isAtEnd()) {
      if (peek() == '.') {
        numberOfDecimals++;
        if (numberOfDecimals > 1) {
          reportError("invalid number", line);
        }
      }
      current++;
    }
    string text = source.substr(start, current - start);
    double d = stod(text);
    addToken(TokenType::NUMBER, Literal(d));
  }

  void identifierTokenize() {
    char c = source[current];
    while (isalnum(c) && !isAtEnd()) {
      
      current++;
      string text = source.substr(start, current - start);
      
      if(KEYWORDS[text]){
        addToken(KEYWORDS[text]);
        return;
      }
      c = source[current];
    }

    string text = source.substr(start, current - start);
    TokenType type = KEYWORDS[text];
    if (!type) {
      addToken(TokenType::IDENTIFIER);
    } else {
      addToken(type);
      // if(type==TokenType::PRINT){
        
      // }
    }
  }
  void scanToken() {
    char c = source[current++];

    switch (c) {
      case '(':
        addToken(TokenType::LEFT_PAREN);
        break;
      case ')':
        addToken(TokenType::RIGHT_PAREN);
        break;
      case '{':
        addToken(TokenType::LEFT_BRACE);
        break;
      case '}':
        addToken(TokenType::RIGHT_BRACE);
        break;
      case ',':
        addToken(TokenType::COMMA);
        break;
      case '.':
        addToken(TokenType::DOT);
        break;
      case '-':
        addToken(TokenType::MINUS);
        break;
      case '+':
        addToken(TokenType::PLUS);
        break;
      case ';':
        addToken(TokenType::SEMICOLON);
        break;
      case '*':
        addToken(STAR);
        break;
   
      case '!':

        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
      case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
      case '<':
        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
      case '>':
        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
      case '/':
        if (match('/')) {
          while (peek() != '\n' && !isAtEnd()) current++;
        } else {
          addToken(SLASH);
        }
        break;
      case ' ':
      case '\r':
      case '\t':
        break;
      case '\n':
        line++;
        break;
      case '"':
        stringTokenize();
        break;
      case 'o':

      default:
        if (isdigit(c)) {
          tokenizedigit();
        } else if (isalpha(c)) {
          identifierTokenize();

        } else {
          reportError("end of file", line);
        }
        break;
    }
  };
};