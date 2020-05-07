#pragma once

#include "types/state.hpp"
#include "types/string.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace qsts {

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
        if (op_ == '+') return left_->eval(s) + right_->eval(s);
        if (op_ == '*') return left_->eval(s) * right_->eval(s);
        if (op_ == '/') return right_->eval(s) / left_->eval(s);
        return 0;
    }

private:
    char op_;
    std::shared_ptr<node> left_;
    std::shared_ptr<node> right_;
};

//! factory for node generation
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
    // variables
    std::vector<std::shared_ptr<variable>> vs_;
    // expression (root node of graph)
    std::shared_ptr<node> expression_;
    double eval(const state& s) {
        if (expression_) {
            expression_->eval(s);
        }
    }
};

}  // namespace qsts
