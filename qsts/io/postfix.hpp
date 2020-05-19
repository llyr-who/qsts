#pragma once

#include "io/infix.hpp"

#include <stack>

namespace qsts {

namespace type_rule {
struct postfix {};
}  // namespace type_rule

using postfix = token_container<type_rule::postfix>;

//! convert infix to postfix
postfix to_postfix(infix&& ifx) {
    std::stack<std::shared_ptr<token>> s;
    auto ts = ifx.move_tokens();
    postfix pfx;
    for (const auto& t : ts) {
        // if t is a number or a variable, push
        // to the string.
        if (t->type() != token::token_type::binary_operation) {
            pfx.add_token(t);
            continue;
        }

        // push to stack if left paraen.
        if (*t == ops_map.at('(')) {
            s.push(t);
            continue;
        }

        // if we encounter a right paraen.
        if (*t == ops_map.at(')')) {
            // pop off until we get to a left paraen.
            while (*s.top() != ops_map.at('(')) {
                pfx.add_token(s.top());
                s.pop();
            }
            s.pop();
            continue;
        }

        // if it an operator
        while (!s.empty() && (s.top())->priority() >= t->priority()) {
            pfx.add_token(s.top());
            s.pop();
        }
        s.push(t);
    }

    while (!s.empty()) {
        pfx.add_token(s.top());
        s.pop();
    }

    return pfx;
}

postfix to_postfix(const std::string& s) {
    return to_postfix(to_infix(s));
}

}  // namespace qsts
