#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include<memory>
#include "declarations/token.hpp"
#include "declarations/environment.hpp"
#include "declarations/expr.hpp"
#include "declarations/stmt.hpp"
#include "declarations/declaration.hpp"
#include "expr.cpp"
#include "stmt.cpp"


#include "declarations/expr.hpp"
#include "declarations/stmt.hpp"

// #include "declarations/token.hpp"
// #include "declaration.cpp"

#include "declaration.cpp"
#include "environment.cpp"

#include "tokenizer.cpp"
// #include "environment.cpp"



#include "parser.cpp"
#include "interpreter.cpp"
// #include "globals.hpp"

using namespace std;



int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "ERORR: Pass the filename to compile" << endl;
    return 0;
  }
  string filename = argv[1];
  cout << "received filename : " << filename << endl;
  string fileinput, line_text;

  ifstream MyReadFile(filename);

  while (getline(MyReadFile, line_text)) {
    fileinput += line_text;
  }

  MyReadFile.close();

  cout << fileinput << endl;
  Tokenizer tokenizer(fileinput);
  tokenizer.display();
  Parser parser(tokenizer.tokens);
  vector<unique_ptr<Decl>> statements = parser.parse();
  
  // // cout<<"parsing done"<<endl;

  

  Interpreter interpreter(std::move(statements));
  interpreter.evaluate();

  
  return 0;
}