#pragma once

#include <list>

#include "qsts/types/infix.hpp"

namespace qsts {
namespace exp {

namespace type_rule {
struct postfix {};
}  // namespace type_rule

using postfix = token_container<type_rule::postfix>;

//! convert infix to postfix
postfix convert(const infix& ifx) {
    std::stack<char> s;
    auto ts = ifx.tokens();
    std::list<token> pfx;
    for (const char& t : ts) {
        // if t is a number or a variable, push
        // to the string.
        if (t.type() != token::token_type::binary_operation) {
            pfx.push_back(t);
            continue;
        }

        // push to stack if left paraen.
        if (t == '(') {
            s.push(t);
            continue;
        }

        // if we encounter a right paraen.
        if (t == ')') {
            // pop off until we get to a left paraen.
            while (s.top() != '(') {
                pfx.push_back(s.top());
                s.pop();
            }
            s.pop();
            continue;
        }

        // if it an operator
        while (!s.empty() && priority(s.top()) >= priority(t)) {
            pfx.push_back(s.top());
            s.pop();
        }
        s.push(t);
    }

    while (!s.empty()) {
        pfx.push_back(s.top());
        s.pop();
    }

    return postfix(std::move(pfx));
}
}  // namespace exp

}  // namespace qsts
}  // namespace qsts
