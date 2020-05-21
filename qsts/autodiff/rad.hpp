#pragma once

#include "io/expression.hpp"
#include "io/postfix.hpp"
#include "io/state.hpp"

namespace qsts {

namespace rad {
class node : public qsts::base::node {
public:
    explicit node(token t) : qsts::base::node(t), value_(0), grad_(0) {}
    void grad(const state& s) {}
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
    auto grad() { return 0.0; }
};

}  // namespace rad

}  // namespace qsts
