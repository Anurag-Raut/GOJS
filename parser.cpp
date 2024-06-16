
#include <iostream>
#include <memory>
#include <vector>

#include "declarations/declaration.hpp"
#include "declarations/expr.hpp"
#include "declarations/stmt.hpp"
#include "declarations/token.hpp"

using namespace std;
class Parser {
 public:
  vector<Token> tokens;
  Parser(vector<Token> tokens) { this->tokens = tokens; }

  vector<shared_ptr<Decl>> parse() {
    vector<shared_ptr<Decl>> declarations;
    while (!isAtEnd()) {
      declarations.push_back(declaration());
      // current++;
      // cout << " current: " << current << " token: " << tokens[current].lexeme
      //      << endl;
    }
    // cout<<"size"<<declarations.size()<<endl;

    return declarations;
  }

  shared_ptr<Expr> expression() { return equality(); }

  shared_ptr<Expr> equality() {
    shared_ptr<Expr> left = comparison();
    if (match({TokenType::EQUAL_EQUAL, TokenType::BANG_EQUAL})) {
      Token op = tokens[current];
      current++;
      shared_ptr<Expr> right = equality();

      return std::make_shared<BinaryExpr>((left), op, (right));
    }

    return left;
  }

  shared_ptr<Expr> comparison() {
    shared_ptr<Expr> left = term();
    if (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS,
               TokenType::LESS_EQUAL})) {
      Token op = tokens[current];
      current++;
      // cout << "OPPP " << op.lexeme << endl;
      shared_ptr<Expr> right = comparison();
      return std::make_shared<BinaryExpr>((left), op, (right));
    }

    return left;
  }

  shared_ptr<Expr> term() {
    shared_ptr<Expr> left = factor();
    if (match({TokenType::PLUS, TokenType::MINUS})) {
      Token op = tokens[current];
      current++;
      shared_ptr<Expr> right = term();

      return std::make_shared<BinaryExpr>((left), op, (right));
    }

    return left;
  }

  shared_ptr<Expr> factor() {
    shared_ptr<Expr> left = unary();
    if (match({TokenType::STAR, TokenType::SLASH})) {
      Token op = tokens[current];
      current++;
      shared_ptr<Expr> right = factor();

      return std::make_shared<BinaryExpr>((left), op, (right));
    }

    return left;
  }

  shared_ptr<Expr> unary() {
    // Expr left = unary();
    if (match({TokenType::BANG})) {
      Token op = tokens[current];
      current++;
      shared_ptr<Expr> right = unary();

      return std::make_shared<UnaryExpr>((op), (right));
    }
    return primary();
  }

  shared_ptr<Expr> primary() {
    // cout<<tokens[current].lexeme<<endl;

    if (match({TokenType::FALSE})) {
      current++;
      return std::make_shared<LiteralExpr>(false);
    }
    if (match({TokenType::TRUE})) {
      current++;
      return std::make_shared<LiteralExpr>(true);
    }
    if (match({TokenType::NIL})) {
      current++;
      return std::make_shared<LiteralExpr>();
    }
    if (match({TokenType::NUMBER, TokenType::STRING})) {
      // cout << "Number " << tokens[current].lexeme << endl;
      current++;
      return std::make_shared<LiteralExpr>(tokens[current - 1].literal);
    }
    if (match({TokenType::LEFT_PAREN})) {
      shared_ptr<Expr> expr = expression();
      consume(RIGHT_PAREN, "Expect ')' after expression.");
      return std::make_shared<GroupingExpr>((expr));
    }
    if (match({TokenType::IDENTIFIER})) {
      // cout<<"hellp "<<tokens[current].lexeme<<endl;
      current++;
      string identifier = tokens[current - 1].lexeme;
      // cout << "identier " << identifier << endl;
      // cout << tokens[current].lexeme << endl;
      if (tokens[current].type == TokenType::LEFT_PAREN) {
        vector<shared_ptr<Expr>> args;
        // cout << "heelo" << endl;
        consume(TokenType::LEFT_PAREN, "expected '(' ");
        while (tokens[current].type != TokenType::RIGHT_PAREN) {
          // cout << "toke s " << tokens[current].lexeme << endl;
          shared_ptr<Expr> expr = expression();
          // cout<<"out expresso " <<tokens[current].type<<endl;

          if (tokens[current].type == TokenType::COMMA) {
            // cout << "consumed comma " << endl;
            consume(TokenType::COMMA, "expected ',' ");

          } else if (tokens[current].type != TokenType::RIGHT_PAREN) {
            runtime_error("error while parsing arguments");
          }

          args.push_back((expr));
        }
        consume(TokenType::RIGHT_PAREN, "expected ')' ");

        // cout << "args " << args.size() << endl;

        return make_shared<CallExpr>(
            identifier, make_shared<vector<shared_ptr<Expr>>>((args)));
      }
      return make_shared<IdentifierExpr>((tokens[current - 1].lexeme));
      // if(variables.find(tokens[current].lexeme)!=variables.end()){
      //   current++;
      //   cout<<"got hrerere"<<endl;
      //   return std::make_shared<LiteralExpr>(variables[tokens[current -
      //   1].lexeme]);
      // }
      // else{
      //   runtime_error("Undefined varaible");
      // }
    }
  }

  bool match(vector<TokenType> types) {
    for (auto type : types) {
      if (tokens[current].type == type) {
        return true;
      }
    }

    return false;
  }

  void consume(TokenType type, string error_message) {
    if (tokens[current].type == type) {
      current++;
      return;
    }

    error(error_message);
  }

  void error(string error_message) {
    runtime_error(error_message(char *));
    return;
  }

  //  private:
  int current = 0;

  shared_ptr<Stmt> statement() {
    if (match({TokenType::PRINT})) {
      current += 1;
      consume(TokenType::LEFT_PAREN, "Expected '(' after print");
      shared_ptr<Expr> expr = (expression());
      // cout<<"toke "<<tokens[current].lexeme<<endl;
      consume(TokenType::RIGHT_PAREN, "Expected ')' after print");

      return make_shared<PrintStmt>((expr));
    } else if (match({TokenType::IDENTIFIER}) &&
               tokens[current + 1].type == TokenType::EQUAL) {
      string variableName = tokens[current].lexeme;
      consume(TokenType::IDENTIFIER, "Expected 'IDENTIFIER' after print");
      consume(TokenType::EQUAL, "Expected '=' after print");

      shared_ptr<Expr> expr = (expression());

      return make_shared<AssignStmt>(variableName, (expr));

    } else if (match({TokenType::RETURN})) {
      current++;
      shared_ptr<Expr> expr = (expression());

      return make_shared<ReturnStmt>((expr));
    } else {
      shared_ptr<Expr> expr = (expression());
      return make_shared<ExprStmt>((expr));
    }
  }

  shared_ptr<Decl> declaration() {
    if (match({TokenType::VAR})) {
      // cout<<"var"<<endl;
      current += 1;

      string name = tokens[current].lexeme;
      current++;
      consume(TokenType::EQUAL, "Expected a \"=\" ");
      shared_ptr<Expr> expr = (expression());

      return make_shared<VarDecl>(name, (expr));
    } else if (match({TokenType::FUNC})) {
      return getFunctionDecl();
    } else if (match({TokenType::IF})) {
      consume(TokenType::IF, "Expected \"if\" ");
      consume(TokenType::LEFT_PAREN, "Expected \"(\" ");

      shared_ptr<Expr> expr = (expression());

      consume(TokenType::RIGHT_PAREN, "Expected \")\" ");

      shared_ptr<BlockDecl> ifBlock = (getBlock());
      if (match({TokenType::ELSE})) {
        consume(TokenType::ELSE, "Expected \")\" ");
        shared_ptr<BlockDecl> elseBlock = (getBlock());

        return make_shared<IfDecl>((expr), (ifBlock), (elseBlock));
      }
      return make_shared<IfDecl>((expr), (ifBlock));

    } else if (match({TokenType::WHILE})) {
      consume(TokenType::WHILE, "Expected \"while\" ");
      consume(TokenType::LEFT_PAREN, "Expected \"while\" ");
      shared_ptr<Expr> expr = (expression());

      consume(TokenType::RIGHT_PAREN, "Expected \"while\" ");
      shared_ptr<BlockDecl> block = (getBlock());

      return make_shared<WhileBlock>((expr), (block));

    } else if (match({TokenType::FOR})) {
      // cout<<"for"<<endl;
      consume(TokenType::FOR, "Expected \"for\" ");
      consume(TokenType::LEFT_PAREN, "Expected \"for\" ");
      shared_ptr<Decl> decl = declaration();
      consume(TokenType::SEMICOLON, "Expected \";\" ");
      shared_ptr<Expr> condition = expression();
      consume(TokenType::SEMICOLON, "Expected \";\" ");
      shared_ptr<Stmt> stmt = statement();
      consume(TokenType::RIGHT_PAREN, "Expected \")\" ");
      shared_ptr<BlockDecl> block = (getBlock());

      return make_shared<ForBlock>(decl, condition, stmt, block);

    } else if (match({TokenType::LEFT_BRACE})) {
      return getBlock();

    } else {
      return make_shared<Statement>((statement()));
      // shared_ptr< Expr>expr=(expression());
      // return make_shared<ExprStmt>(ExprStmt((expr)));
    }
  }

 private:
  bool isAtEnd() {
    if (current >= tokens.size() ||
        tokens[current].type == TokenType::ENDOFFILE) {
      return true;
    }
    return false;
  }

  shared_ptr<FuncDecl> getFunctionDecl() {
    // func add(int a , int b){
    //  print(a)
    //  print (b)
    //  return a+b;
    // }
    current++;

    string functionName = tokens[current++].lexeme;
    consume(TokenType::LEFT_PAREN, "Expected '('");
    // // consumeing arguments
    // vector<Parameter> params ;
    shared_ptr<vector<Parameter>> params = make_shared<vector<Parameter>>();
    while (tokens[current].type != TokenType::RIGHT_PAREN) {
      if (tokens[current].type != TokenType::IDENTIFIER) {
        runtime_error("expected Identifier in function argument");
      }

      Parameter param = Parameter(tokens[current++].lexeme);
      params->push_back(param);

      if (tokens[current].type == TokenType::COMMA) {
        consume(TokenType::COMMA, "expected ','in function argument");
      } else if ((tokens[current].type != TokenType::RIGHT_PAREN)) {
        runtime_error("expected ',' or ') in function argument");
      }

      cout << current << " curren " << endl;
    }

    consume(TokenType::RIGHT_PAREN, "Expected ')'");
    shared_ptr<BlockDecl> block = getBlock();
    cout << "out" << endl;

    return (make_shared<FuncDecl>(functionName, (params), (block)));
  }

  shared_ptr<BlockDecl> getBlock() {
    consume(TokenType::LEFT_BRACE, "Expected '{'");

    shared_ptr<vector<shared_ptr<Decl>>> decls =
        make_shared<vector<shared_ptr<Decl>>>();

    while (tokens[current].type != TokenType::RIGHT_BRACE) {
      shared_ptr<Decl> decl = (declaration());
      decls->push_back((decl));
    }

    consume(TokenType::RIGHT_BRACE, "Expected '}'");
    return make_shared<BlockDecl>((decls));
  }
};