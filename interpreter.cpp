
#include <iostream>
#include <memory>

#include "declarations/declaration.hpp"
#include "declarations/expr.hpp"

using namespace std;
class Interpreter {
 public:
  vector<shared_ptr<Decl>> declarations;

  Interpreter(vector<shared_ptr<Decl>> declarations) {
    // cout<<"size " <<declarations.size()<<endl;
    this->declarations = (declarations);
  }

 

  void evaluate() {
    //     Literal literal = stmts->evaluate();
    // cout<<"evaluated value"<<declarations.size()<<endl;
    //     // if(literal.value.has_value()){
    //         // Literal l1((string)"asdasd");

    //    Enviliteral.printLiteral();
    Environment *globalEnv = new Environment();
     shared_ptr<FuncDecl> timedecl=make_shared<FuncDecl>("time");
    
    globalEnv->setFunction("time",timedecl);
  
    for (auto &decl : declarations) {
      decl->execute(globalEnv);
      // cout << "hello" << endl;
    }


    // }
  }
};

