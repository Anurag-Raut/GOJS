
#pragma once
#include <any>
#include <memory>

// #include "expr.hpp"
// #include "token.hpp"


using namespace std;
class Stmt {
 public:
  Stmt() = default;
  virtual void evaluate(Environment *env) = 0;
};

class ExprStmt : public Stmt {
 public:
  shared_ptr<Expr> expr;
  ExprStmt(shared_ptr<Expr> expr) ;

  void evaluate(Environment *env);
};

class PrintStmt : public Stmt {
 public:
  shared_ptr<Expr> expr;

  PrintStmt(shared_ptr<Expr> expr);

  void evaluate(Environment *env) ;
};

class AssignStmt : public Stmt {
 public:
  shared_ptr<Expr> expr;
  string variableName;

  AssignStmt(string variableName, shared_ptr<Expr> expr);

  void evaluate(Environment *env) ;
};

class ReturnStmt : public Stmt {
  public:
    shared_ptr <Expr> expr;

    ReturnStmt(shared_ptr <Expr> expr);
  void evaluate(Environment *env) ;

};

