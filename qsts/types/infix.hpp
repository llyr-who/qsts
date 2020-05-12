#pragma once

#include "types/token.hpp"

namespace qsts {
namespace exp {

namespace type_rule {
struct infix {
    // add "valid" method to check validity
};
}  // namespace type_rule

using infix = token_container<type_rule::infix>;

infix string_to_infix(const std::string& s) {
    std::string str = s;
    return infix(std::move(tokenise(str)));
}

}  // namespace exp
}  // namespace qsts
