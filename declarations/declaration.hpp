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
  // virtual void execute(vector<shared_ptr<Expr>> args, Environment *globalEnv) =0;

};



class Statement : public Decl {
 public:
  shared_ptr<Stmt> stmt;

  Statement(shared_ptr<Stmt> stmt);

  void execute(Environment *env) override;
};

class VarDecl : public Decl {
 public:
  string name;
  shared_ptr<Expr> value;

  VarDecl(string name, shared_ptr<Expr> value);

  void execute(Environment *env) override;
};

class BlockDecl : public Decl {
 public:
  shared_ptr<vector<shared_ptr<Decl>>> decls;

  BlockDecl(shared_ptr<vector<shared_ptr<Decl>>> decls);

  void execute(Environment *env) override;

  Literal executeFunc(Environment *env);
  
};

class IfDecl : public Decl {
 public:
  shared_ptr<Expr> expr;
  shared_ptr<BlockDecl> ifBlock;
  shared_ptr<BlockDecl> elseBlock = NULL;

  IfDecl(shared_ptr<Expr> expr, shared_ptr<BlockDecl> ifBlock,
         shared_ptr<BlockDecl> elseBlock);
  IfDecl(shared_ptr<Expr> expr, shared_ptr<BlockDecl> ifBlock);

  void execute(Environment *env) override;
};

class WhileBlock : public Decl {
 public:
  shared_ptr<Expr> expr;
  shared_ptr<BlockDecl> block;

  WhileBlock(shared_ptr<Expr> expr, shared_ptr<BlockDecl> block);

  void execute(Environment *env) override;
};

class ForBlock : public Decl {
 public:
  shared_ptr<Decl> declaration;
  shared_ptr<Expr> condition;
    shared_ptr<Stmt> doStatement;


  shared_ptr<BlockDecl> block;

  ForBlock(shared_ptr<Decl> declaration,shared_ptr<Expr> condition,shared_ptr<Stmt> doStatement, shared_ptr<BlockDecl> block);

  void execute(Environment *env) override;
};

class FuncDecl : public Decl {
 public:
  string name;

  shared_ptr<vector<Parameter>> parameters;
  shared_ptr<BlockDecl> block;

  FuncDecl(string name, shared_ptr<vector<Parameter>> parameters,
           shared_ptr<BlockDecl> block);
  void execute(Environment *env) override;

  Literal executeArgs(shared_ptr<vector<shared_ptr<Expr>>>args,Environment *env) ;

};


