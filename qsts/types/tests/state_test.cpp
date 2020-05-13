#include "types/state.hpp"
#include "types/graph.hpp"

#include "gtest/gtest.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

using namespace qsts;

TEST(graph, make_node_type) {
    std::string apb = "A+B";
    qsts::state s0 = {{"A", 1.0}, {"B", 1.0}};
    auto g0 = postfix_to_graph(string_to_postfix(apb));
    ASSERT_EQ(eval(g0, s0), 2.0);

    std::string apr = "Anthony+Rose";
    qsts::state s1 = {{"Anthony", 1.0}, {"Rose", 1.0}};
    auto g1 = postfix_to_graph(string_to_postfix(apr));
    ASSERT_EQ(eval(g1, s1), 2.0);
}

