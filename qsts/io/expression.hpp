#pragma once

#include "types/string.hpp"
#include "algo/convert.hpp"

namespace qsts {

// everything in this namespace needs to
// be moved to an external repo.
namespace external_types {

class node {
    enum class type { Variable, Constant, BinaryOperation };

    type type_;
};

class v_node : public node {};

class c_node : public node {};

class b_o_node : public node {};

class expression {};

}  // namespace external_types

// forward declaration
postfix convert(const infix&);
external_types::expression convert(const postfix&);

external_types::expression expression(const infix& ifx) {
    // convert infix to postfix
    auto pfx = convert(ifx);
    // convert postfix to expression and return
    return convert(pfx);
}

}  // namespace qsts
