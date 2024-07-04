
#include "declarations/declaration.hpp"

#include <chrono>
#include <ctime>
#include <string>
#include <unordered_map>
#include <vector>

#include "declarations/ReturnExpection.hpp"
#include "declarations/stmt.hpp"
#include "declarations/token.hpp"

using namespace std;

Statement::Statement(shared_ptr<Stmt> stmt) { this->stmt = (stmt); }

void Statement::execute(Environment *env) { stmt->evaluate(env); }

VarDecl::VarDecl(string name, shared_ptr<Expr> value) {
  this->name = name;
  this->value = (value);
}

void VarDecl::execute(Environment *env) {
  // cout << "doing var declartion of " << name << " ";

  Literal l1 = value->evaluate(env);
  // cout << "received Litera for declaration of " << name << " is : ";
  // l1.printLiteral();
  env->setVariable(name, l1);
  // variables[name].printLiteral();
}

BlockDecl::BlockDecl(shared_ptr<vector<shared_ptr<Decl>>> decls) {
  this->decls = (decls);
}

void BlockDecl::execute(Environment *env) {
  Environment *childEnv = new Environment();
  childEnv->parent = env;
  for (const auto &decl : *decls) {
    decl->execute(childEnv);
  }
}

IfDecl::IfDecl(shared_ptr<Expr> expr, shared_ptr<BlockDecl> ifBlock,
               shared_ptr<BlockDecl> elseBlock) {
  this->expr = (expr);
  this->ifBlock = (ifBlock);
  this->elseBlock = (elseBlock);
}
IfDecl::IfDecl(shared_ptr<Expr> expr, shared_ptr<BlockDecl> ifBlock) {
  this->expr = (expr);
  this->ifBlock = (ifBlock);
  this->elseBlock = NULL;
}

void IfDecl::execute(Environment *env) {
  Literal ans = expr->evaluate(env);
  // cout<<"if expr" ;
  // ans.printLiteral();
  if (!ans.checkType<bool>()) {
    ifBlock->execute(env);

  } else if (ans.checkType<bool>() && any_cast<bool>(ans.value)) {
    ifBlock->execute(env);

  } else if (elseBlock) {
    // cout << "executing else" << endl;
    elseBlock->execute(env);
    // cout << "done else" << endl;
  }
}

WhileBlock::WhileBlock(shared_ptr<Expr> expr, shared_ptr<BlockDecl> block) {
  this->expr = (expr);
  this->block = (block);
}

void WhileBlock::execute(Environment *env) {
  Literal ans = expr->evaluate(env);
  while (!ans.checkType<bool>() ||
         ans.checkType<bool>() && any_cast<bool>(ans.value)) {
    block->execute(env);
    ans = expr->evaluate(env);
  }
}

ForBlock::ForBlock(shared_ptr<Decl> declaration, shared_ptr<Expr> condition,
                   shared_ptr<Stmt> doStatement, shared_ptr<BlockDecl> block) {
  this->declaration = declaration;
  this->condition = condition;
  this->doStatement = doStatement;
  this->block = block;
}

void ForBlock::execute(Environment *env) {
  Environment *childEnv = new Environment();
  childEnv->parent = env;
  declaration->execute(childEnv);

  Literal ans = condition->evaluate(childEnv);

  while (!ans.checkType<bool>() ||
         ans.checkType<bool>() && any_cast<bool>(ans.value)) {
    block->execute(childEnv);
    doStatement->evaluate(childEnv);
    ans = condition->evaluate(childEnv);
  }
}

FuncDecl::FuncDecl(string name, shared_ptr<vector<Parameter>> parameters,
                   shared_ptr<BlockDecl> block
                   //  ,shared_ptr<vector<type_index>> returnTypes
) {
  this->name = name;
  this->parameters = (parameters);
  this->block = (block);
}

FuncDecl::FuncDecl(string name) {
 this->name=name;
}
Literal FuncDecl::executeArgs(shared_ptr<vector<shared_ptr<Expr>>> args,
                              Environment *env) {
  // cout<<"staring function execution : "<<name<<endl;
  if (this->name == "time") {
    auto now = std::chrono::system_clock::now();
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    auto value = now_ms.time_since_epoch().count();


    return Literal((double)(value));
  }
  vector<Literal> lits;
  Environment *childEnv = new Environment();
  childEnv->parent = env;
  for (int index = 0; index < args->size(); index++) {
    // lits.push_back(arg->evaluate(env));
    // cout<<"paramters "<<parameters->at(index).name<<endl;
    childEnv->setVariable(parameters->at(index).name,
                          args->at(index)->evaluate(childEnv));
  }
  try {
    block->execute(childEnv);
  } catch (ReturnException &v) {
    // cout<<"recived exception ";
    // v.value.printLiteral();
    return v.value;
  }

  return Literal();
}

void FuncDecl::execute(Environment *env) {
  env->setFunction(this->name, std::shared_ptr<FuncDecl>(this));
}

// getVariable(){

// }
