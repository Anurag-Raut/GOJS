#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "environment.hpp"
#include "stmt.hpp"
#include "token.hpp"

using namespace std;

class Parameter {
 public:
  string type;
  string name;

  Parameter(string name, string type) {
    this->name = name;
    this->type = type;
  }
};

class Decl {
 public:
  // virtual void execute() = 0;
  virtual void execute(Environment *globalEnv) = 0;
};

class FuncDecl : public Decl {
 public:
  string name;
  vector<unique_ptr<Stmt>> statements;

  FuncDecl(string name, vector<unique_ptr<Stmt>> statements);

  void execute(Environment *env);
};

class Statement : public Decl {
 public:
  unique_ptr<Stmt> stmt;

  Statement(unique_ptr<Stmt> stmt);

  void execute(Environment *env);
};

class VarDecl : public Decl {
 public:
  string name;
  unique_ptr<Expr> value;

  VarDecl(string name, unique_ptr<Expr> value);

  void execute(Environment *env);
};

class BlockDecl : public Decl {
 public:
  unique_ptr<vector<unique_ptr<Decl>>> decls;

  BlockDecl(unique_ptr<vector<unique_ptr<Decl>>> decls);

  void execute(Environment *env);
};

class IfDecl : public Decl {
 public:
  unique_ptr<Expr> expr;
  unique_ptr<BlockDecl> ifBlock;
  unique_ptr<BlockDecl> elseBlock = NULL;

  IfDecl(unique_ptr<Expr> expr, unique_ptr<BlockDecl> ifBlock,
         unique_ptr<BlockDecl> elseBlock);
  IfDecl(unique_ptr<Expr> expr, unique_ptr<BlockDecl> ifBlock);

  void execute(Environment *env);
};

class WhileBlock : public Decl {
 public:
  unique_ptr<Expr> expr;
  unique_ptr<BlockDecl> block;

  WhileBlock(unique_ptr<Expr> expr, unique_ptr<BlockDecl> block);

  void execute(Environment *env);
};

class FuncDecl : public Decl {
 public:
  string name;

  unique_ptr<vector<unique_ptr<Parameter>>> parameters;
  unique_ptr<BlockDecl> block;

  FuncDecl(string name, unique_ptr<vector<unique_ptr<Parameter>>> parameters,
           unique_ptr<BlockDecl> block);
  void execute(Environment *env);

};

// getVariable(){

// }
