#include "types/expression.hpp"

#include "gtest/gtest.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

TEST(expression, make_node_type) {
    // note that cn1 and cn2 have different types, according to
    // decltype.
    auto cn1 = qsts::make_node('c');
    auto cn2 = std::make_shared<qsts::variable>('c');
    ASSERT_EQ(cn1->type(), cn2->type());

    auto cn3 = qsts::make_node('1');
    auto cn4 = std::make_shared<qsts::constant>('1');
    ASSERT_EQ(cn3->type(), cn4->type());

    // form the expression "c+1"
    auto cn5 = qsts::make_node('+', cn1, cn3);
    auto cn6 =
        std::make_shared<qsts::binary_operation>('+', cn1, cn3);
    ASSERT_EQ(cn5->type(), cn6->type());
}

