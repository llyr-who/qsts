#include "autodiff/rad.hpp"
#include "io/expression.hpp"
#include "io/postfix.hpp"

#include "gtest/gtest.h"

using namespace qsts;

TEST(rad, basic) {
    auto e = rad::expression("2*A+B");
    state s = {{"A", 2}, {"B", 1}};
    auto g = e.grad(s);

    auto e1 = rad::expression("2*A*B");
    state s1 = {{"A", 2}, {"B", 1}};
    auto g1 = e1.grad(s1);
}

TEST(rad, grad) {
    auto e = rad::expression("(A+B) + A + (A+B)");
    state s = {{"A", 1}, {"B",1}};
    auto g = e.grad(s);
}
