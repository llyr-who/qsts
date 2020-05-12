#pragma once

#include "types/postfix.hpp"
#include "types/state.hpp"
#include "types/token.hpp"

#include <cstdlib>
#include <iostream>

namespace qsts {
namespace exp {

namespace type_rule {
struct graph {};
}  // namespace type_rule

using graph = token_container<type_rule::graph>;

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
    // the top of the stack is now the root.
    // put this at the end.
    pfx_tokens.push_back(s.top());
    return graph(std::move(pfx_tokens));
}



}  // namespace exp
}  // namespace qsts
