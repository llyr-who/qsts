#include "autodiff/rad.hpp"
#include "io/expression.hpp"
#include "io/postfix.hpp"

#include "gtest/gtest.h"

using namespace qsts;

TEST(rad, basic) {
    auto e = rad::expression("A+B");
    state s = {{"A", 2}, {"B", 1}};
    ASSERT_EQ(e[s], 3);
}

