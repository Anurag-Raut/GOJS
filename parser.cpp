
#include <iostream>
#include <memory>
#include <vector>

#include "expr.hpp"
#include "stmt.hpp"
#include "token.hpp"
#include "declaration.hpp"
using namespace std;
class Parser {
 public:
  vector<Token> tokens;
  Parser(vector<Token> tokens) { this->tokens = tokens; }

  vector<unique_ptr<Decl>> parse() {
    vector<unique_ptr<Decl>> declarations;
    while (!isAtEnd()) {
      declarations.push_back(declaration());
      // current++;
      // cout<<" current: "<<current<<" token: "<<tokens[current].lexeme<<endl;
    }
    // cout<<"size"<<declarations.size()<<endl;

    return declarations;
  }

  unique_ptr<Expr> expression() { return equality(); }

  unique_ptr<Expr> equality() {
    unique_ptr<Expr> left = comparison();
    if (match({TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL})) {
      Token op = tokens[current];
      current++;
      unique_ptr<Expr> right = equality();

      return std::make_unique<BinaryExpr>(std::move(left), op,
                                          std::move(right));
    }

    return left;
  }

  unique_ptr<Expr> comparison() {
    unique_ptr<Expr> left = term();
    if (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS,
               TokenType::LESS_EQUAL})) {
      Token op = tokens[current];
      current++;
      unique_ptr<Expr> right = comparison();

      return std::make_unique<BinaryExpr>(std::move(left), op,
                                          std::move(right));
    }

    return left;
  }

  unique_ptr<Expr> term() {
    unique_ptr<Expr> left = factor();
    if (match({TokenType::PLUS, TokenType::MINUS})) {
      Token op = tokens[current];
      current++;
      unique_ptr<Expr> right = term();

      return std::make_unique<BinaryExpr>(std::move(left), op,
                                          std::move(right));
    }

    return left;
  }

  unique_ptr<Expr> factor() {
    unique_ptr<Expr> left = unary();
    if (match({TokenType::STAR, TokenType::SLASH})) {
      Token op = tokens[current];
      current++;
      unique_ptr<Expr> right = factor();

      return std::make_unique<BinaryExpr>(std::move(left), op,
                                          std::move(right));
    }

    return left;
  }

  unique_ptr<Expr> unary() {
    // Expr left = unary();
    if (match({TokenType::BANG})) {
      Token op = tokens[current];
      current++;
      unique_ptr<Expr> right = unary();

      return std::make_unique<UnaryExpr>(std::move(op), std::move(right));
    }
    return primary();
  }

  unique_ptr<Expr> primary() {
    // cout<<tokens[current].lexeme<<endl;

    if (match({TokenType::FALSE})) {
      current++;
      return std::make_unique<LiteralExpr>(false);
    }
    if (match({TokenType::TRUE})) {
      current++;
      return std::make_unique<LiteralExpr>(true);
    }
    if (match({TokenType::NIL})) {
      current++;
      return std::make_unique<LiteralExpr>();
    }
    if (match({TokenType::NUMBER, TokenType::STRING})) {
      current++;
      return std::make_unique<LiteralExpr>(tokens[current - 1].literal);
    }
    if (match({TokenType::LEFT_PAREN})) {
      unique_ptr<Expr> expr = expression();
      consume(RIGHT_PAREN, "Expect ')' after expression.");
      return std::make_unique<GroupingExpr>(std::move(expr));
    }
    if(match({TokenType::IDENTIFIER})){
          // cout<<"hellp "<<tokens[current].lexeme<<endl;
          current++;
        return make_unique<IdentifierExpr>(std::move(tokens[current-1].lexeme));
      // if(variables.find(tokens[current].lexeme)!=variables.end()){
      //   current++;
      //   cout<<"got hrerere"<<endl;
      //   return std::make_unique<LiteralExpr>(variables[tokens[current - 1].lexeme]);
      // }
      // else{
      //   runtime_error("Undefined varaible");
      // }
    }
  }

  bool match(vector<TokenType> types) {
    for (auto type : types) {
      if (tokens[current].type == type) {
        return true;
      }
    }

    return false;
  }

  void consume(TokenType type, string error_message) {
    if (tokens[current].type == type) {
      current++;
      return;
    }

    error(error_message);
  }

  void error(string error_message) {
    runtime_error(error_message(char *));
    return;
  }

//  private:
  int current = 0;

  unique_ptr<Stmt> statement() {
    if (match({TokenType::PRINT})) {
      current+=1;
      consume(TokenType::LEFT_PAREN,"Expected '(' after print");
      unique_ptr<Expr> expr=std::move(expression());
        // cout<<"toke "<<tokens[current].lexeme<<endl;
        consume(TokenType::RIGHT_PAREN,"Expected ')' after print");

       return make_unique<PrintStmt>(std::move(expr));
    }
    else {
      unique_ptr< Expr>expr=std::move(expression());
      return make_unique<ExprStmt>(ExprStmt(std::move(expr)));

    }
  }


   unique_ptr<Decl> declaration() {
    if (match({TokenType::VAR})) {
      // cout<<"var"<<endl;
      current+=1;
      
      string name =tokens[current].lexeme;
      current++;
      consume(TokenType::EQUAL,"Expected a \"=\" ");
      unique_ptr<Expr> expr = std::move(expression());
      // expr->evaluate().printLiteral();

    // cout<<"cure "<<current<<" tok " <<tokens[current].lexeme<<endl;
      // unique_ptr<Expr> expr=std::move(expression());
      
       return make_unique<VarDecl>(name,std::move(expr));
    }
    else {
        return make_unique<Statement>(std::move(statement()));
      // unique_ptr< Expr>expr=std::move(expression());
      // return make_unique<ExprStmt>(ExprStmt(std::move(expr)));

    }
  }

  private:
    bool isAtEnd(){
      if(current>=tokens.size() || tokens[current].type==TokenType::ENDOFFILE){
        return true;
      }
      return false;
    }
};