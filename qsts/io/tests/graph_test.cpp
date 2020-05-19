#include "io/graph.hpp"
#include "io/postfix.hpp"

#include "gtest/gtest.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

using namespace qsts;

TEST(graph, eval) {
    std::string e1 = "(A+B)+A*(A+B)";
    auto g0 = to_graph(to_postfix(e1));
    qsts::state s0 = {{"A", 2.0}, {"B", 1.0}};
    qsts::state s1 = {{"A", 2.0}, {"B", 2.0}};
    qsts::state s2 = {{"A", 2.0}, {"B", 0.0}};
    qsts::state s3 = {{"A", -1.0}, {"B", 1.0}};
    qsts::state s4 = {{"A", 1.0}, {"B", 1.0}};
    ASSERT_EQ(g0[s0], 9.0);
    ASSERT_EQ(g0[s1], 12.0);
    ASSERT_EQ(g0[s2], 6.0);
    ASSERT_EQ(g0[s3], 0.0);
    ASSERT_EQ(g0[s4], 4.0);
}

void fill_count_map(std::map<std::shared_ptr<node>, int>& nodes,
                    const std::shared_ptr<node>& head) {
    auto it_h = nodes.insert(std::make_pair(head, 1));
    if (!it_h.second) {
        it_h.first->second++;
    }

    if (head->left() != nullptr) {
        fill_count_map(nodes, head->left());
    }
    if (head->right() != nullptr) {
        fill_count_map(nodes, head->right());
    }
}

auto unique_tester(const std::shared_ptr<node>& head) {
    std::map<std::shared_ptr<node>, int> nodes;
    fill_count_map(nodes, head);
    return nodes;
}

TEST(graph, unique) {
    std::string e1 = "(A+B)+A*(A+B)";
    auto g0 = to_graph(to_postfix(e1));
    // gets the shared pointer of the head of the graph
    auto nodes = unique_tester(g0.get());
    node a_plus_b = node(token("+"), token("A"), token("B"));
    for (const auto& n : nodes) {
        if (n.first->to_string() == "A") {
            ASSERT_EQ(n.second, 3);
            continue;
        }
        if (n.first->to_string() == "B") {
            ASSERT_EQ(n.second, 2);
            continue;
        }
        if (*n.first == a_plus_b) {
            ASSERT_EQ(n.second, 2);
            continue;
        }
    }
}
