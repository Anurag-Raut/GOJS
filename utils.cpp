
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
void reportError(string error,int line){
    throw runtime_error(error+"line: "+ to_string(line));
}