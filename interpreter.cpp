
#include <iostream>
#include <memory>
#include "expr.hpp"
#include "stmt.hpp"

using namespace std;
class Interpreter{

    public:
        vector<unique_ptr<Stmt>> stmts;
        
        Interpreter(vector<unique_ptr<Stmt>>stmts){
            // cout<<"size " <<stmts.size()<<endl;
            this->stmts=std::move(stmts);
        }


       void evaluate(){
    //     Literal literal = stmts->evaluate();
    //     cout<<"evaluated value"<<endl;
    //     // if(literal.value.has_value()){
    //         // Literal l1((string)"asdasd");

    //    literal.printLiteral();

            for(auto &stmt:stmts){
                    stmt->evaluate();
            }

        // }
       }


        
        


};