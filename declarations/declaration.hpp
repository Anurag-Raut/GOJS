#pragma once
#include <string>
#include <unordered_map>
#include <vector>


#include "stmt.hpp"
#include"expr.hpp"
#include "token.hpp"

using namespace std;

class Parameter {
 public:

  string name;

  Parameter(string name) {
    this->name = name;
 
  }
};

class Decl {
 public:
  // virtual void execute() = 0;
  virtual void execute(Environment *globalEnv) = 0;
  // virtual void execute(vector<unique_ptr<Expr>> args, Environment *globalEnv) =0;

};



class Statement : public Decl {
 public:
  unique_ptr<Stmt> stmt;

  Statement(unique_ptr<Stmt> stmt);

  void execute(Environment *env) override;
};

class VarDecl : public Decl {
 public:
  string name;
  unique_ptr<Expr> value;

  VarDecl(string name, unique_ptr<Expr> value);

  void execute(Environment *env) override;
};

class BlockDecl : public Decl {
 public:
  unique_ptr<vector<unique_ptr<Decl>>> decls;

  BlockDecl(unique_ptr<vector<unique_ptr<Decl>>> decls);

  void execute(Environment *env) override;

  Literal executeFunc(Environment *env);
  
};

class IfDecl : public Decl {
 public:
  unique_ptr<Expr> expr;
  unique_ptr<BlockDecl> ifBlock;
  unique_ptr<BlockDecl> elseBlock = NULL;

  IfDecl(unique_ptr<Expr> expr, unique_ptr<BlockDecl> ifBlock,
         unique_ptr<BlockDecl> elseBlock);
  IfDecl(unique_ptr<Expr> expr, unique_ptr<BlockDecl> ifBlock);

  void execute(Environment *env) override;
};

class WhileBlock : public Decl {
 public:
  unique_ptr<Expr> expr;
  unique_ptr<BlockDecl> block;

  WhileBlock(unique_ptr<Expr> expr, unique_ptr<BlockDecl> block);

  void execute(Environment *env) override;
};

class FuncDecl : public Decl {
 public:
  string name;

  unique_ptr<vector<Parameter>> parameters;
  unique_ptr<BlockDecl> block;

  FuncDecl(string name, unique_ptr<vector<Parameter>> parameters,
           unique_ptr<BlockDecl> block);
  void execute(Environment *env) override;

  Literal executeArgs(unique_ptr<vector<unique_ptr<Expr>>>args,Environment *env) ;

};


