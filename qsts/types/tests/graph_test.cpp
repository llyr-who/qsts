#include "types/graph.hpp"

#include "gtest/gtest.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

TEST(graph, make_node_type) {
    // note that cn1 and cn2 have different types, according to
    // decltype.
    auto cn1 = qsts::exp::make_node('c');
    auto cn2 = std::make_shared<qsts::exp::variable>('c');
    ASSERT_EQ(cn1->type(), cn2->type());

    auto cn3 = qsts::exp::make_node('1');
    auto cn4 = std::make_shared<qsts::exp::constant>('1');
    ASSERT_EQ(cn3->type(), cn4->type());

    // form the graph "c+1"
    auto cn5 = qsts::exp::make_node('+', cn1, cn3);
    auto cn6 = std::make_shared<qsts::exp::binary_operation>('+', cn1, cn3);
    ASSERT_EQ(cn5->type(), cn6->type());
}

