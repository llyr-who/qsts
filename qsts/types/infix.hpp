#pragma once

#include <list>

#include "qsts/types/token.hpp"

namespace qsts {
namespace exp {

namespace type_rule {
struct infix {
    // add "valid" method to check validity
};
}  // namespace type_rule

using infix = token_container<type_rule::infix>;

infix convert(std::string s) {
    std::list<token> ts;
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    size_t pos = 0;
    std::string t;
    while ((pos = s.find_first_of("+-/*()")) != std::string::npos) {
        ts.push_back(token(s.substr(0, pos)));
        ts.push_back(token(s[pos]);
        s.erase(0,pos+1);
    }
    return infix(std::move(ts));
}

}  // namespace exp
}  // namespace qsts
