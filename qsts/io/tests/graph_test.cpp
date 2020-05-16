#include "io/graph.hpp"
#include "io/postfix.hpp"

#include "gtest/gtest.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

using namespace qsts;

TEST(graph, basic) {
    std::string e1 = "(A+B)+A*(A+B)";
    auto g = to_graph(to_postfix(e1));

    g.print();
    /* auto A = g;
     while(A->left() != nullptr) {
         A = A->left();
     }
     ASSERT_EQ(A->to_string(), "A");
     ASSERT_EQ(A->parents().size(), 3);
 
    std::string apb = "A+B";
    qsts::state s0 = {{"A", 1.0}, {"B", 1.0}};
    auto g0 = to_graph(to_postfix(apb));
    ASSERT_EQ(g0[s0], 2.0);
    */
}
