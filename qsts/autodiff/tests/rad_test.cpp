#include "autodiff/rad.hpp"
#include "io/expression.hpp"
#include "io/postfix.hpp"

#include "gtest/gtest.h"

using namespace qsts;

TEST(rad, basic) {
    auto e = rad::expression("2*A+B");
    state s = {{"A", 2}, {"B", 1}};
	state g = { {"A", 2}, {"B", 1} };
	ASSERT_EQ(e.grad(s), g);

    auto e1 = rad::expression("2*A*B");
    state s1 = {{"A", 2}, {"B", 1}};
	state g1 = { {"A", 2}, {"B", 4} };
    ASSERT_EQ(e1.grad(s1), g1);
}

TEST(rad, grad) {
    auto e = rad::expression("(A+B) + A + (A+B)");
    state s = {{"A", 1}, {"B",1}};
	state g = { {"A", 3}, {"B", 2} };
    ASSERT_EQ(e.grad(s), g);

	auto e1 = rad::expression("(A+B) + 2*(B*A) * (A+B) * (B*A)");
	state s1 = { {"A", 1}, {"B", 1} };
	state g1 = { {"A", 11}, {"B", 11} };
	ASSERT_EQ(e1.grad(s1), g1);
}
