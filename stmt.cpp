#include "declarations/stmt.hpp"

#include <any>
#include <iostream>
#include <memory>

#include "declarations/token.hpp"
#include "declarations/expr.hpp"
#include "declarations/environment.hpp"
#include "declarations/ReturnExpection.hpp"

using namespace std;

ExprStmt::ExprStmt(shared_ptr<Expr> expr) { this->expr = (expr); }

void ExprStmt::evaluate(Environment *env) {
  Literal l = expr->evaluate(env);
  // l.printLiteral();
}

PrintStmt::PrintStmt(shared_ptr<Expr> expr) { this->expr = (expr); }

void PrintStmt::evaluate(Environment *env) {
  // cout<<"printin"<<endl;
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

AssignStmt::AssignStmt(string variableName, shared_ptr<Expr> expr) {
  this->expr = (expr);
  this->variableName = variableName;
}

void AssignStmt::evaluate(Environment *env) {
  // cout<<"huhhh"<<endl;
    Literal l2=expr->evaluate(env);
    // l2.printLiteral();
    // cout<<"assigning now"<<endl;
  env->assignValue(variableName, l2, env);
      // cout<<"assigning done"<<endl;

}

ReturnStmt::ReturnStmt(shared_ptr<Expr> expr){
  this->expr = (expr);
}


  void ReturnStmt::evaluate(Environment *env){
    Literal l=expr->evaluate(env);
    ReturnException r (l);
    throw r;
  }
