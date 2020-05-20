#include "autodiff/rad.hpp"
#include "io/graph.hpp"
#include "io/postfix.hpp"

#include "gtest/gtest.h"

using namespace qsts;

TEST(expression, basic) {
    auto e = expression("A+B");
    state s = {{"A", 1}, {"B", 1}};
    auto g = grad(e, s);
}

