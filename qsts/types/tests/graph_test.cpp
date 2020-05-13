#include "types/graph.hpp"
#include "types/postfix.hpp"

#include "gtest/gtest.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

using namespace qsts;

TEST(graph, make_node_type) {
    std::string apb = "A+B";
    auto g = postfix_to_graph(string_to_postfix(apb));
}

