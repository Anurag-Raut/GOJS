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
  template <typename T>
  bool checkType(vector<Literal> l1) {
    for (auto &r : l1) {
      if (r.value.type() != typeid(T)) {
        return false;
      }
    }

    return true;
  }

  Literal evaluate() override {
    Literal left = this->left->evaluate();
    Literal right = this->right->evaluate();

    // cout<<" left "<<left<<" right "<<right<<" op
    // "<<op.type<<TokenType::PLUS<<endl;
    switch (op.type) {
      case TokenType::PLUS:
        // cout<<to_string(left.value)<<endl;
        if (checkType<string>({left, right})) {
          // cout << "string" << endl;
          return Literal(any_cast<string>(left.value) +
                         any_cast<string>(right.value));
        } else if (checkType<double>({left, right})) {
          // cout << "double" << endl;

          return Literal(any_cast<double>(left.value) +
                         any_cast<double>(right.value));
        } else {
          runtime_error("both operands not same type");
        }

        break;
        case TokenType::MINUS:
        if (checkType<double>({left, right})) {
          return Literal(any_cast<double>(left.value) -
                         any_cast<double>(right.value));
        } else {
          runtime_error("both operands not double");
        }

        break;
      case TokenType::STAR:
        if (checkType<double>({left, right})) {
          return Literal(any_cast<double>(left.value) *
                         any_cast<double>(right.value));
        } else {
          runtime_error("both operands not double");
        }

        break;

      case TokenType::SLASH:
        if (checkType<double>({left, right})) {
          // cout << "double" << endl;

          return Literal(any_cast<double>(left.value) /
                         any_cast<double>(right.value));
        } else {
          runtime_error("both operands not double");
        }

        break;

      case TokenType::EQUAL_EQUAL:
        if (checkType<bool>({left, right})) {
          if (any_cast<bool>(left.value) == any_cast<bool>(right.value)) {
            return Literal(true);
          } else {
            return Literal(false);
          }
        }

        break;

      case TokenType::BANG_EQUAL:
        if (checkType<bool>({left, right})) {
          if (any_cast<bool>(left.value) != any_cast<bool>(right.value)) {
            return Literal(true);
          } else {
            return Literal(false);
          }
        }

        break;

      case TokenType::GREATER:
        if (checkType<double>({left, right})) {
          if (any_cast<double>(left.value) > any_cast<double>(right.value)) {
            return Literal(true);
          } else {
            return Literal(false);
          }
        }
        break;
      case TokenType::GREATER_EQUAL:
        if (checkType<double>({left, right})) {
          if (any_cast<double>(left.value) >= any_cast<double>(right.value)) {
            return Literal(true);
          } else {
            return Literal(false);
          }
        }
        break;
      case TokenType::LESS:
        if (checkType<double>({left, right})) {
          if (any_cast<double>(left.value) < any_cast<double>(right.value)) {
            return Literal(true);
          } else {
            return Literal(false);
          }
        }
        break;
      case TokenType::LESS_EQUAL:
        if (checkType<double>({left, right})) {
          if (any_cast<double>(left.value) <= any_cast<double>(right.value)) {
            return Literal(true);
          } else {
            return Literal(false);
          }
        }

        break;
      default:
        runtime_error("No matching operation defined");
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
    // literal.printLiteral();

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
