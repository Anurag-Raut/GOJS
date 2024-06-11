
#include <vector>

#include "token.hpp"
class Parser {
 public:
  vector<Token> tokens;
  Parser(vector<Token> tokens) { this.tokens = tokens }
};