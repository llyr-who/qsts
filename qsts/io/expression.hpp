#pragma once

#include "types/string.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>

namespace qsts {

// everything in this namespace needs to
// be moved to an external repo.
namespace external_types {

enum class node_type { variable, constant, binary_operation };

class node {
public:
    virtual node_type type() = 0;
};

class variable : public node {
public:
    variable(const char& v) : v_(v){};
    node_type type() { return node_type::variable; }

private:
    char v_;
};

class constant : public node {
public:
    constant(const char& c) : c_(c){};
    node_type type() { return node_type::variable; }

private:
    int c_;
};

class binary_operation : public node {
public:
    binary_operation(const char& op, std::shared_ptr<node> l,
                     std::shared_ptr<node> r)
        : op_(op), left_(l), right_(r){};
    node_type type() { return node_type::variable; }

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

class expression {
    std::unique_ptr<node> root_;
};

}  // namespace external_types

// forward declaration
postfix convert(const infix&);
external_types::expression convert(const postfix&);

// factory for expression generation.
external_types::expression expression(const infix& ifx) {
    // convert infix to postfix
    auto pfx = convert(ifx);
    // convert postfix to expression and return
    return convert(pfx);
}

}  // namespace qsts
