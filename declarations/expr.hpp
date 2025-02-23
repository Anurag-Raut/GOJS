#pragma once 
#include <memory>

#include "token.hpp"
#include "environment.hpp"

using namespace std;

class Expr {
 public:
  Expr() = default;

  // virtual Literal evaluate() = 0;
  virtual Literal evaluate(Environment *env)=0;
};

class BinaryExpr : public Expr {
 public:
  std::shared_ptr<Expr> left;
  std::shared_ptr<Expr> right;
  Token op;

  BinaryExpr(std::shared_ptr<Expr> left, Token op,
             std::shared_ptr<Expr> right) ;
  template <typename T>
  bool checkType(vector<Literal> l1) ;

  Literal evaluate(Environment *env) override ;
};

class UnaryExpr : public Expr {
 public:
  std::shared_ptr<Expr> right;
  Token op;

  UnaryExpr(Token op, std::shared_ptr<Expr> right);
  

  Literal evaluate(Environment *env) override ;
};

class LiteralExpr : public Expr {
 public:
  Literal literal;
  LiteralExpr(Literal literal) ;
  LiteralExpr() ;

  Literal evaluate(Environment *env) override ;
};

class IdentifierExpr :public Expr {
public:
  string name;
  IdentifierExpr()=default;
  IdentifierExpr(string name);

  Literal evaluate(Environment *env) override;

};

class GroupingExpr : public Expr {
 public:
  std::shared_ptr<Expr> expr;
  GroupingExpr(std::shared_ptr<Expr> expr) ;

  Literal evaluate(Environment *env) override ;
};

class CallExpr : public Expr {
    public:
    string identidier;
    shared_ptr<vector<shared_ptr<Expr>>> args;
    CallExpr(string identidier,shared_ptr<vector<shared_ptr<Expr>>> args);

    Literal evaluate(Environment *env) override ;

};
