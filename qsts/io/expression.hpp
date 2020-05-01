#pragma once

#include "io/state.hpp"
#include "types/string.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace qsts {

// everything in this namespace needs to
// be moved to an external repo.
namespace external {

enum class node_type { variable, constant, binary_operation };

class node {
public:
    virtual node_type type() = 0;
    virtual double eval(const state& s) = 0;
};

class variable : public node {
public:
    variable(const char& v) : v_(v){};
    node_type type() { return node_type::variable; }
    double eval(const state& s) { return s.at(v_); }

private:
    char v_;
};

class constant : public node {
public:
    constant(const char& c) : c_(c){};
    node_type type() { return node_type::variable; }
    double eval(const state& s) { return static_cast<double>(c_); }

private:
    double c_;
};

class binary_operation : public node {
public:
    binary_operation(const char& op, std::shared_ptr<node> l,
                     std::shared_ptr<node> r)
        : op_(op), left_(l), right_(r){};
    node_type type() { return node_type::variable; }
    double eval(const state& s) {
        double rval;
        if (op_ == '+') rval = left_->eval(s) + right_->eval(s);
        if (op_ == '*') rval = left_->eval(s) * right_->eval(s);
        if (op_ == '/') rval = right_->eval(s) / left_->eval(s);
        std::cout << rval << std::endl;
        return rval;
    }

private:
    char op_;
    std::shared_ptr<node> left_;
    std::shared_ptr<node> right_;
};

//! factory for node generation
//! we will be iterating over strings
//! so the first argument is a const char&
std::shared_ptr<node> make_node(const char& t,
                                std::shared_ptr<node> lhs = nullptr,
                                std::shared_ptr<node> rhs = nullptr) {
    // if it is a char then it could be a variable
    if (std::isalpha(t)) {
        return std::make_shared<variable>(t);
    }
    if (std::isdigit(t)) {
        return std::make_shared<constant>(t);
    }
    if (lhs == nullptr || rhs == nullptr) {
        throw std::runtime_error("one of the operands is null");
    }
    return std::make_shared<binary_operation>(t, lhs, rhs);
}

struct expression {
    std::shared_ptr<node> root_;
    double eval(const state& s) {
        if (root_) {
            root_->eval(s);
        }
    }
};

}  // namespace external

// forward declaration
postfix convert(const infix&);
external::expression convert(const postfix&);

// factory for expression generation.
external::expression expression(const infix& ifx) {
    // convert infix to postfix
    auto pfx = convert(ifx);
    // convert postfix to expression and return
    return convert(pfx);
}

}  // namespace qsts
