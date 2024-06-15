#pragma once

#include <any>
#include <stdexcept>
#include "token.hpp"

using namespace std;

class ReturnException : public std::runtime_error {
public:
    ReturnException(Literal value) : std::runtime_error(""), value(value) {}

    // const std::any& getValue() const { return value; }

// private:
    Literal value;
};
