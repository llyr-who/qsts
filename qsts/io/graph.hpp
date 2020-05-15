#pragma once

#include "io/postfix.hpp"
#include "io/state.hpp"
#include "io/token.hpp"

#include <cstdlib>
#include <iostream>

namespace qsts {

using graph = std::shared_ptr<token>;

//! convert postfix to expression
graph postfix_to_graph(postfix&& pfx) {
    std::stack<std::shared_ptr<token>> s;
    auto pfx_tokens = pfx.move_tokens();

    for (auto& t : pfx_tokens) {
        if (t->type() != token::token_type::binary_operation) {
            // variable or constant
            s.push(t);
            continue;
        }
        // else get the last two things on the stack
        auto op1 = s.top();
        s.pop();
        auto op2 = s.top();
        s.pop();
        // set them as children
        t->set_left_child(std::move(op1));
        t->set_right_child(std::move(op2));
        // push it back on the stack
        s.push(t);
    }
    return s.top();
}

}  // namespace qsts
