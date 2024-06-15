
#include <iostream>
#include <memory>

#include "declarations/declaration.hpp"
#include "declarations/expr.hpp"

using namespace std;
class Interpreter {
 public:
  vector<unique_ptr<Decl>> declarations;

  Interpreter(vector<unique_ptr<Decl>> declarations) {
    // cout<<"size " <<declarations.size()<<endl;
    this->declarations = std::move(declarations);
  }

 

  void evaluate() {
    //     Literal literal = stmts->evaluate();
    // cout<<"evaluated value"<<endl;
    //     // if(literal.value.has_value()){
    //         // Literal l1((string)"asdasd");

    //    Enviliteral.printLiteral();
    Environment *globalEnv = new Environment();

  
    for (auto &decl : declarations) {
      decl->execute(globalEnv);
      // cout << "hello" << endl;
    }

    // delete globalEnv;

    // }
  }
};

