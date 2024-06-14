
#pragma once


using namespace std;
class FuncDecl;
class Environment {
 public:
  Environment* parent = NULL;
  std::unordered_map<std::string, Literal> variables;
    std::unordered_map<std::string, unique_ptr<FuncDecl>> functions;


   Literal getVariable(string key, Environment* env) ;

  void setVariable(string key, Literal value);

  void assignValue(string key, Literal value, Environment* env ) ;

  unique_ptr<FuncDecl> getFunction(string key,Environment* env);
  void setFunction(string key,unique_ptr<FuncDecl> func);

};

