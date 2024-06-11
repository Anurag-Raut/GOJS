
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

#ifndef UTILS_HPP
#define UTILS_HPP

void reportError(string error,int line){
    throw runtime_error(error+"line: "+ to_string(line));

  

}

  #endif 