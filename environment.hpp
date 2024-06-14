
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <iostream>
#include "declarations/environment.hpp"





  Literal Environment::getVariable(string key, Environment* env) {
    if (env->variables.find(key) != env->variables.end()) {
      return env->variables[key];
    } else if (env->parent == NULL) {
      throw runtime_error("varaible \"" + key + "\" undefined");
    } else {
      return getVariable(key, env->parent);
    }
  }

  void Environment::setVariable(string key, Literal value) {
    this->variables[key] = value;
    // cout<<"done "<<key<<endl;
  }

  void Environment::assignValue(string key, Literal value, Environment* env ) {
    if (env->variables.find(key) != env->variables.end()) {
       env->variables[key]=value;
       return ;
    } else if (env->parent == NULL) {
      throw runtime_error("cannot assing varaible \"" + key + "\" before declaration");
    } else {
      return assignValue(key, value, env->parent);
    }
  }

