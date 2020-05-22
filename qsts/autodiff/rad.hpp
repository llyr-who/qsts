#pragma once

#include "io/expression.hpp"
#include "io/postfix.hpp"
#include "io/state.hpp"

namespace qsts {

namespace rad {
class node : public qsts::base::node {
public:
    explicit node(token t) : qsts::base::node(t), value_(0), grad_(0) {}
    void grad(const state& s) {
        if (type() == token::token_type::binary_operation) {
            return;
        }
        if (type() == token::token_type::variable) {
            return;
        }
        if (type() == token::token_type::constant) {
            return;
        }
    }
    double value_;
    double grad_;
};

//! The idea here is that you generate a base expression
//! given a type of node then inherit from it to extend
//! functionality
class expression : public qsts::base::expression<node> {
public:
    expression(postfix&& pfx) : qsts::base::expression<node>(std::move(pfx)){};
    expression(std::string s)
        : qsts::base::expression<node>(std::move(to_postfix(s))){};
    auto grad(const state& s) {
        // fire off a recursive gradient operation.
        head_->grad(s);
        // iterate through unique variables and pick out grads w.r.t each.
        return 0.0;
    }
};

}  // namespace rad

}  // namespace qsts
