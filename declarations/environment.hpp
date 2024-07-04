
#pragma once


using namespace std;
class FuncDecl;
class Environment {
 public:
  Environment* parent = NULL;
  std::unordered_map<std::string, Literal> variables;
    std::unordered_map<std::string, shared_ptr<FuncDecl>> functions;


   Literal getVariable(string key, Environment* env) ;

  void setVariable(string key, Literal value);

  void assignValue(string key, Literal value, Environment* env ) ;

  shared_ptr<FuncDecl> getFunction(string key,Environment* env);
  void setFunction(string key,shared_ptr<FuncDecl> func);

};

