#pragma once

#include <algorithm>
#include <iostream>
#include <stack>

#include "io/expression.hpp"
#include "types/string.hpp"

namespace qsts {

int priority(const char& op) {
    if (op == '(') return -1;
    if (op == '^') return 0;
    if (op == '-' || op == '+') return 1;
    if (op == '*' || op == '/') return 2;
    return 3;
}

//! convert infix to postfix
postfix convert(const infix& ifx) {
    std::stack<char> s;

    std::string ifx_string = ifx.value(), pfx;

    for (const char& t : ifx_string) {
        // ignore spaces
        if (t == ' ') continue;

        // if t is a number or a variable, push
        // to the string.
        if (std::isalnum(t)) {
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

    return postfix(pfx);
}

//! convert postfix to expression
external_types::expression convert(const postfix& pfx) {
    return external_types::expression();
}

}  // namespace qsts
