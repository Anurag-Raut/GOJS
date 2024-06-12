
#include <iostream>
#include <memory>
#include "expr.hpp"
#include "declaration.hpp"

using namespace std;
class Interpreter{

    public:
        vector<unique_ptr<Decl>> declarations;
        
        Interpreter(vector<unique_ptr<Decl>>declarations){
            // cout<<"size " <<declarations.size()<<endl;
            this->declarations=std::move(declarations);
        }


       void evaluate(){
    //     Literal literal = stmts->evaluate();
    //     cout<<"evaluated value"<<endl;
    //     // if(literal.value.has_value()){
    //         // Literal l1((string)"asdasd");

    //    literal.printLiteral();

            for(auto &decl:declarations){
                    decl->execute();
            }

        // }
       }


        
        


};