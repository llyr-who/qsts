#pragma once

#include "algo/convert.hpp"
#include "types/string.hpp"

namespace qsts {

// everything in this namespace needs to
// be moved to an external repo.
namespace external_types {

template <typename node_type>
class node {
public:
    node(node_type t);

private:
    node_type t_;
};

namespace node_type {
    struct variable {
        std::string s_;
    };

    struct constant {
        double d_;
    };

    struct binary_operation {
        node<binary_operation>* left;
        node<binary_operation>* right;
    };
}


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
