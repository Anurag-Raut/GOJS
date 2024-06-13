
#include "token.hpp"

#include<stdexcept>
#include <string>
#include <unordered_map>

#ifndef ENV_HPP
#define ENV_HPP

class Environment{
public :
    Environment* parent = NULL;
    std::unordered_map<std::string, Literal> variables;


    Literal getVariable(string key,Environment *env){
        if(env->variables.find(key)!=env->variables.end()){
            return env->variables[key];
        }
        else if(env->parent==NULL){
            throw runtime_error("varaible \""+key+"\" undefined");
        }
        else {
            return getVariable(key,env->parent);
        }
    }

    void setVariable(string key,Literal value){
        this->variables[key]=value;
                // cout<<"done "<<key<<endl;

    }



};

#endif