// #include <any>
#include "declarations/expr.hpp"
#include "declarations/declaration.hpp"
#include <memory>
#include <stdexcept>

using namespace std;

BinaryExpr::BinaryExpr(std::unique_ptr<Expr> left, Token op,
                       std::unique_ptr<Expr> right) {
  this->left = std::move(left);
  this->right = std::move(right);
  this->op = op;
}
template <typename T>
bool BinaryExpr::checkType(vector<Literal> l1) {
  for (auto &r : l1) {
    if (r.value.type() != typeid(T)) {
      return false;
    }
  }

  return true;
}

Literal BinaryExpr::evaluate(Environment *env) {
  Literal left = this->left->evaluate(env);
  Literal right = this->right->evaluate(env);

  switch (op.type) {
    case TokenType::PLUS:
      if (checkType<string>({left, right})) {
        return Literal(any_cast<string>(left.value) +
                       any_cast<string>(right.value));
      } else if (checkType<double>({left, right})) {
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
      } else if (checkType<double>({left, right})) {
        if (any_cast<double>(left.value) == any_cast<double>(right.value)) {
          return Literal(true);
        } else {
          return Literal(false);
        }
      } else if (checkType<string>({left, right})) {
        if (any_cast<string>(left.value) == any_cast<string>(right.value)) {
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

UnaryExpr::UnaryExpr(Token op, std::unique_ptr<Expr> right) {
  this->right = std::move(right);
  this->op = op;
}

Literal UnaryExpr::evaluate(Environment *env) {
  Literal right = this->right->evaluate(env);

  switch (op.type) {
    case TokenType::BANG:
      return !any_cast<bool>(right.value);
      break;

    default:
      break;
  }
}

LiteralExpr::LiteralExpr(Literal literal) { this->literal = literal; }
LiteralExpr::LiteralExpr() { this->literal = Literal(); }

Literal LiteralExpr::evaluate(Environment *env) {
  // literal.printLiteral();
  // cout<<"gegeg"<<endl;

  return literal;
}

IdentifierExpr::IdentifierExpr(string name) { this->name = name; }

Literal IdentifierExpr::evaluate(Environment *env) {
  // literal.printLiteral();
  // cout<<"sad "<<name<<endl;
  // variables[name].printLiteral();

  return env->getVariable(name, env);
}

GroupingExpr::GroupingExpr(std::unique_ptr<Expr> expr) {
  this->expr = std::move(expr);
}

Literal GroupingExpr::evaluate(Environment *env) { return expr->evaluate(env); }

CallExpr::CallExpr(string identidier, unique_ptr<vector<unique_ptr<Expr>>> args) {
  this->identidier = identidier;
  this->args = std::move(args);
}

Literal CallExpr::evaluate(Environment *env) {
    unique_ptr<FuncDecl> func= move(env->getFunction(this->identidier,env));

    func->executeArgs(std::move(this->args),env);
    
    return Literal("nullopt");
}

