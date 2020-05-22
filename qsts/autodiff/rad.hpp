#pragma once

#include "io/expression.hpp"
#include "io/postfix.hpp"
#include "io/state.hpp"

namespace qsts {

namespace rad {
class node : public qsts::base::node {
public:
    explicit node(token t) : qsts::base::node(t), grad_(0) {}

    void grad(const state& s) {
        std::cout << to_string() << "grad " << grad_ << std::endl; 
        if (type() == token::token_type::binary_operation) {
            if (to_string() == "*") {
                std::static_pointer_cast<node>(left())->grad_ +=
                    grad_ * (*right())[s];
                std::static_pointer_cast<node>(right())->grad_ +=
                    grad_ * (*left())[s];
            }
            if (to_string() == "+") {
                std::static_pointer_cast<node>(left())->grad_ += grad_;
                std::static_pointer_cast<node>(right())->grad_ += grad_;
            }
            std::static_pointer_cast<node>(left())->grad(s);
            std::static_pointer_cast<node>(right())->grad(s);
            return;
        }
        if (type() == token::token_type::constant) {
            grad_ = 0;
            return;
        }
    }

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
        // set root gradient to 1. df/df = 1
        head_->grad_ = 1;
        // fire off evaluations;
        (*head_)[s];
        // fire off derivatives.
        head_->grad(s);
        // iterate through unique variables and pick out grads w.r.t each.
        for (const auto& v : variables_) {
            std::cout << v->to_string() << v->grad_ << std::endl;
        }
        return 0.0;
    }

private:
    std::vector<double> grads_;
};

}  // namespace rad

}  // namespace qsts
