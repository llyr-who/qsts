#pragma once

#include "io/token.hpp"

namespace qsts {

namespace type_rule {
struct infix {
    // add "valid" method to check validity
};
}  // namespace type_rule

using infix = token_container<type_rule::infix>;

infix to_infix(std::string s) {
    infix ifx;
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    size_t pos = 0;
    std::string t;
    while ((pos = s.find_first_of("+-/*()")) != std::string::npos) {
        ifx.add_token(std::make_shared<token>(s.substr(0, pos)));
        ifx.add_token(std::make_shared<token>(s[pos]));
        s.erase(0, pos + 1);
    }
    if (s.size() > 0) {
        ifx.add_token(std::make_shared<token>(s));
    }
    return ifx;
}

}  // namespace qsts
