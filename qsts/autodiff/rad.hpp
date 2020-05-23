#pragma once

#include "io/expression.hpp"
#include "io/postfix.hpp"
#include "io/state.hpp"

namespace qsts {

namespace rad {
class node : public qsts::base::node {
public:
    explicit node(token t) : qsts::base::node(t), grad_(0), visit_count_(0) {}

    void grad(const state& s) {
        // Do not propagate untill all parents have
        // touched their child. I do not advocate this.
        if (++visit_count_ < parents().size() && !parents().empty()) {
            return;
        }

        if (visit_count_ > parents().size()) {
            // we have now visited this node more
            // than we should have which suggests
            // that we want a different gradient.
            grad_ = parents().empty() ? 1 : 0;
            visit_count_ = 0;
        }

        // carry out grad
        if (type() == token::token_type::binary_operation) {
            if (to_string() == "*") {
                std::static_pointer_cast<node>(left())->grad_ +=
                    grad_ * (*right())[s];
                std::static_pointer_cast<node>(right())->grad_ +=
                    grad_ * (*left())[s];
            } else if (to_string() == "+") {
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
    int visit_count_;
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
        state grad = s;
        for (const auto& v : variables_) {
            grad[v->to_string()] = v->grad_;
        }
        return grad;
    }
};

}  // namespace rad

}  // namespace qsts
