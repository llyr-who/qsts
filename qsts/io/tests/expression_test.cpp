#include "io/expression.hpp"

// REALLY do not like having to include this here.
#include "algo/convert.hpp"

#include "gtest/gtest.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

TEST(expression, make_node_type) {
    // note that cn1 and cn2 have different types, according to
    // decltype.
    auto cn1 = qsts::external::make_node('c');
    auto cn2 = std::make_shared<qsts::external::variable>('c');
    ASSERT_EQ(cn1->type(), cn2->type());

    auto cn3 = qsts::external::make_node('1');
    auto cn4 = std::make_shared<qsts::external::constant>('1');
    ASSERT_EQ(cn3->type(), cn4->type());

    // form the expression "c+1"
    auto cn5 = qsts::external::make_node('+', cn1, cn3);
    auto cn6 =
        std::make_shared<qsts::external::binary_operation>('+', cn1, cn3);
    ASSERT_EQ(cn5->type(), cn6->type());
}

