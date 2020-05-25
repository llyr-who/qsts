#include "autodiff/rad.hpp"
#include "io/expression.hpp"
#include "io/postfix.hpp"

#include "gtest/gtest.h"

using namespace qsts;

TEST(rad, basic) {
    auto e = rad::expression("2*A+B");
    state s = {{"A", 2}, {"B", 1}};
    state g = {{"A", 2}, {"B", 1}};
    ASSERT_EQ(e.grad(s), g);

    auto e1 = rad::expression("2*A*B");
    state s1 = {{"A", 2}, {"B", 1}};
    state g1 = {{"A", 2}, {"B", 4}};
    ASSERT_EQ(e1.grad(s1), g1);

	auto e2 = rad::expression("A/B");
	state s2 = { {"A", 1.0}, {"B", 2.0} };
	state g2 = { {"A", 0.5}, {"B", -0.25} };
	ASSERT_EQ(e2.grad(s2), g2);

	auto e3 = rad::expression("2*A-B");
	state s3 = { {"A", 2}, {"B", 1} };
	state g3 = { {"A", 2}, {"B", -1} };
	ASSERT_EQ(e3.grad(s3), g3);

    auto e4 = rad::expression("A");
    state s4 = {{"A", 2}};
	state g4 = { {"A", 1}};
    ASSERT_EQ(e4.grad(s4), g4);
}

TEST(rad, grad_2d) {
    auto e = rad::expression("(A+B) + A + (A+B)");
    state s = {{"A", 1}, {"B", 1}};
    state g = {{"A", 3}, {"B", 2}};
    ASSERT_EQ(e.grad(s), g);

    auto e1 = rad::expression("(A+B) + 2*(B*A) * (A+B) * (B*A)");
    state s1 = {{"A", 1}, {"B", 1}};
    state g1 = {{"A", 11}, {"B", 11}};
    ASSERT_EQ(e1.grad(s1), g1);
}

TEST(rad, grad_3d) {
    auto e = rad::expression("x*x + y*y + z*z");
    state s = {{"x", 1}, {"y", 1}, {"z", 1}};
    state g = {{"x", 2}, {"y", 2}, {"z", 2}};
    ASSERT_EQ(e.grad(s), g);
}
