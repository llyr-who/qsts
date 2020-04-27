#pragma once

#include <stack>

namespace qsts {

using infix = std::string;
using postfix = std::string;

postfix convert(const infix& infx) {
    for (const auto& t : infx) {
        std::cout << t << std::endl;
    }
}

}  // namespace qsts
