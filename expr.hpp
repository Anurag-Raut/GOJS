#include <any>
#include <memory>
#include <stdexcept>

#include "token.hpp"
#include "utils.hpp"

using namespace std;

#ifndef EXPR_HPP
#define EXPR_HPP

class Expr {
 public:
  Expr() = default;

  virtual Literal evaluate() = 0;
};

class BinaryExpr : public Expr {
 public:
  std::unique_ptr<Expr> left;
  std::unique_ptr<Expr> right;
  Token op;

  BinaryExpr(std::unique_ptr<Expr> left, Token op,
             std::unique_ptr<Expr> right) {
    this->left = std::move(left);
    this->right = std::move(right);
    this->op = op;
  }

  Literal evaluate() override {
    Literal left = this->left->evaluate();
    Literal right = this->right->evaluate();
    cout << "Left ";
    left.printLiteral();
    cout << "Right ";
    right.printLiteral();

    // cout<<" left "<<left<<" right "<<right<<" op
    // "<<op.type<<TokenType::PLUS<<endl;
    switch (op.type) {
      case TokenType::PLUS:
        // cout<<to_string(left.value)<<endl;
        if (left.value.type() == typeid(string) &&
            right.value.type() == typeid(string)) {
          cout << "string" << endl;
          return Literal(any_cast<string>(left.value) +
                         any_cast<string>(right.value));
        } else if (left.value.type() == typeid(double) &&
                   right.value.type() == typeid(double)) {
          cout << "double" << endl;

          return Literal(any_cast<double>(left.value) +
                         any_cast<double>(right.value));
        }
        else {
          runtime_error("both operands not same type");
        }
        case TokenType::STAR:
          if (left.value.type() == typeid(double) &&
                   right.value.type() == typeid(double)) {
          cout << "double" << endl;

          return Literal(any_cast<double>(left.value) *
                         any_cast<double>(right.value));
        }
        else {
          runtime_error("both operands not double");
        }
        

      default:
        break;
    }
  }
};

class UnaryExpr : public Expr {
 public:
  std::unique_ptr<Expr> right;
  Token op;

  UnaryExpr(Token op, std::unique_ptr<Expr> right) {
    this->right = std::move(right);
    this->op = op;
  }

  Literal evaluate() override {
    Literal right = this->right->evaluate();

    switch (op.type) {
      case TokenType::BANG:
        return !any_cast<bool>(right.value);
        break;

      default:
        break;
    }
  }
};

class LiteralExpr : public Expr {
 public:
  Literal literal;
  LiteralExpr(Literal literal) { this->literal = literal; }
  LiteralExpr() { this->literal = Literal(); }

  Literal evaluate() override {
    literal.printLiteral();

    return literal;
  }
};

class GroupingExpr : public Expr {
 public:
  std::unique_ptr<Expr> expr;
  GroupingExpr(std::unique_ptr<Expr> expr) { this->expr = std::move(expr); }

  Literal evaluate() override { return expr->evaluate(); }
};

#endif  // EXPR_HPP
