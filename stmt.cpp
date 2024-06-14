#include "declarations/stmt.hpp"

#include <any>
#include <iostream>
#include <memory>

#include "declarations/token.hpp"

using namespace std;

ExprStmt::ExprStmt(unique_ptr<Expr> expr) { this->expr = std::move(expr); }

void ExprStmt::evaluate(Environment *env) {
  Literal l = expr->evaluate(env);
  // l.printLiteral();
}

PrintStmt::PrintStmt(unique_ptr<Expr> expr) { this->expr = std::move(expr); }

void PrintStmt::evaluate(Environment *env) {
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

AssignStmt::AssignStmt(string variableName, unique_ptr<Expr> expr) {
  this->expr = std::move(expr);
  this->variableName = variableName;
}

void AssignStmt::evaluate(Environment *env) {
  env->assignValue(variableName, expr->evaluate(env), env);
}
