#include <any>
#include <memory>

#include "expr.hpp"
#include "token.hpp"

#ifndef STMT_HPP
#define STMT_HPP ;
using namespace std;
class Stmt {
 public:
  Stmt() = default;
  virtual void evaluate(Environment *env) = 0;
};

class ExprStmt : public Stmt {
 public:
  unique_ptr<Expr> expr;
  ExprStmt(unique_ptr<Expr> expr) { this->expr = std::move(expr); }

  void evaluate(Environment *env) {
    Literal l = expr->evaluate(env);
    // l.printLiteral();
  }
};

class PrintStmt : public Stmt {
 public:
  unique_ptr<Expr> expr;

  PrintStmt(unique_ptr<Expr> expr) { this->expr = std::move(expr); }

  void evaluate(Environment *env) {
    any value = expr->evaluate(env).value;
    if (value.type() == typeid(string)) {
      cout << any_cast<string>(value) << endl;
    } else if (value.type() == typeid(double)) {
      cout << any_cast<double>(value) << endl;
    } else if (value.type() == typeid(bool)) {
      cout << any_cast<bool>(value) << endl;
    } else {
      cout << "NIL" << endl;
    }
  }
};

class AssignStmt : public Stmt {
 public:
  unique_ptr<Expr> expr;
  string variableName;

  AssignStmt(string variableName, unique_ptr<Expr> expr) {
    this->expr = std::move(expr);
    this->variableName = variableName;
  }

  void evaluate(Environment *env) {
    env->assignValue(variableName, expr->evaluate(env), env);
  }
};

#endif;