
#include <iostream>
#include <memory>
#include "expr.hpp"

using namespace std;
class Interpreter{

    public:
        unique_ptr<Expr> expr;

        Interpreter(unique_ptr<Expr> expr){
            this->expr=std::move(expr);
        }


       void evaluate(){
        Literal literal = expr->evaluate();
        cout<<"evaluated value"<<endl;
        // if(literal.value.has_value()){
            // Literal l1((string)"asdasd");

       literal.printLiteral();

        // }
       }


        
        


};