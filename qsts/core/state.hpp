#pragma once

#include <map>
#include "core/token.hpp"

namespace qsts {

using state = std::map<std::string, double>;

double eval(const std::shared_ptr<token>& t, const state& s) {
    if (t->type() == token::token_type::binary_operation) {
        if (t->as_string() == "+") return eval(t->right(), s) + eval(t->left(), s);
        if (t->as_string() == "-") return eval(t->right(), s) - eval(t->left(), s);
        if (t->as_string() == "/") return eval(t->right(), s) / eval(t->left(), s);
        if (t->as_string() == "*") return eval(t->right(), s) * eval(t->left(), s);
    }
    if (t->type() == token::token_type::variable) {
        return s.at(t->as_string());
    }
    if (t->type() == token::token_type::constant) {
        return t->as_double();
    }
    return 0;
}
}  // namespace qsts
