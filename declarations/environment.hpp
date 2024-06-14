

#include "token.hpp"



class Environment {
 public:
  Environment* parent = NULL;
  std::unordered_map<std::string, Literal> variables;

   Literal getVariable(string key, Environment* env) ;

  void setVariable(string key, Literal value);

  void assignValue(string key, Literal value, Environment* env ) ;
};

