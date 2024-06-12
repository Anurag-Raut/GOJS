
#include <string>
#include <vector>
#include <unordered_map>

#include "stmt.hpp"
#include "token.hpp"
#include "globals.hpp"

using namespace std;

#ifndef DECL_HPP
#define DECL_HPP



class Decl {
    public:
  virtual void execute() = 0;
};

class FuncDecl : public Decl {
 public:
  string name;
  vector<unique_ptr<Stmt>> statements;

  FuncDecl(string name, vector<unique_ptr<Stmt>> statements) {
    this->name = name;
    this->statements = std::move(statements);
  }

  void execute() {
    for (auto& stmt : statements) {
      stmt->evaluate();
    }
  }


};

class Statement : public Decl {
    public:
    unique_ptr<Stmt> stmt;

    Statement(unique_ptr<Stmt> stmt){
        this->stmt=std::move(stmt);
    }


    void execute(){
        stmt->evaluate();
    }
};

class VarDecl : public Decl {
 public:
  string name;
  unique_ptr<Expr> value;

  VarDecl(string name, unique_ptr<Expr> value) {
    this->name = name;
    this->value = std::move(value);
  }

  void execute() {
    variables[name]=value->evaluate();
    // variables[name].printLiteral();
  }


};


// getVariable(){

// }

template <typename T>
class Argument {
 public:
  T type;
  string name;

  Argument(string name, T type) {
    this->name = name;
    this->type = type;
  }
};






#endif
