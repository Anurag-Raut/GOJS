
#include <string>
#include <vector>
#include <unordered_map>

#include "stmt.hpp"
#include "token.hpp"
#include "environment.hpp"

using namespace std;

#ifndef DECL_HPP
#define DECL_HPP



class Decl {
    public:
  // virtual void execute() = 0;
  virtual void execute(Environment *globalEnv)=0;
};

class FuncDecl : public Decl {
 public:
  string name;
  vector<unique_ptr<Stmt>> statements;

  FuncDecl(string name, vector<unique_ptr<Stmt>> statements) {
    this->name = name;
    this->statements = std::move(statements);
  }

  void execute(Environment *env) {
     

    for (auto& stmt : statements) {
      stmt->evaluate(env);
    }
  }


};

class Statement : public Decl {
    public:
    unique_ptr<Stmt> stmt;

    Statement(unique_ptr<Stmt> stmt){
        this->stmt=std::move(stmt);
    }


    void execute(Environment *env){
        stmt->evaluate(env);
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

  void execute(Environment *env) {
    // cout<<"doing var declartion"<<endl;
    // Literal l1=value->evaluate(env);
    // l1.printLiteral();
    env->setVariable(name,value->evaluate(env));
    // variables[name].printLiteral();


  }


};


class BlockDecl : public Decl {

  public :
    unique_ptr<vector<unique_ptr<Decl>>> decls;

    BlockDecl(unique_ptr<vector<unique_ptr<Decl>>> decls) {
 
    this->decls = std::move(decls);
  }

  void execute(Environment *env) {
     Environment *childEnv=new Environment();
      childEnv->parent=env;
    for( const auto& decl: *decls){
      decl->execute(childEnv);
    }
    
  }

};

class IfDecl : public Decl {

  public :
    unique_ptr<Expr> expr;
    unique_ptr<BlockDecl> block;

    IfDecl(unique_ptr<Expr> expr,unique_ptr<BlockDecl> block) {
    this->expr=std::move(expr);
    this->block = std::move(block);
  }

  void execute(Environment *env) {
    Literal ans=expr->evaluate(env);
    if(!ans.checkType<bool>()){
            block->execute(env);

    }
    else if(ans.checkType<bool>() &&  any_cast<bool>(ans.value) ){

      block->execute(env);
     
    }
  
    
  }

};


// getVariable(){

// }

template <typename T>
class Paramter {
 public:
  T type;
  string name;

  Paramter(string name, T type) {
    this->name = name;
    this->type = type;
  }
};






#endif
