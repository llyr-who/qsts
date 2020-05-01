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
external::expression convert(const postfix& pfx) {
    external::expression e;
    std::stack<std::shared_ptr<external::node>> s;
    auto pfx_string = pfx.value();

    for (const char& c : pfx_string) {
        if (std::isalnum(c)) {
            // variable or constant
            s.push(external::make_node(c));
            continue;
        }
        // else get the last two things on the stack
        auto op1 = s.top();
        s.pop();
        auto op2 = s.top();
        s.pop();
        s.push(external::make_node(c, op1, op2));
        e.root_ = s.top();
    }
    return e;
}

}  // namespace qsts
