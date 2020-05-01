#include "algo/convert.hpp"
#include "io/state.hpp"

#include "gtest/gtest.h"

TEST(convert, infix_to_postfix) {
    qsts::infix e1("A*B+C/D");
    auto pf1 = qsts::convert(e1);
    ASSERT_EQ(pf1, qsts::postfix("AB*CD/+"));

    qsts::infix e2("A*(B+C)/D");
    auto pf2 = qsts::convert(e2);
    ASSERT_EQ(pf2, qsts::postfix("ABC+*D/"));

    qsts::infix e3("A*(B+C/D)");
    auto pf3 = qsts::convert(e3);
    ASSERT_EQ(pf3, qsts::postfix("ABCD/+*"));
}

TEST(convert, postfix_to_expression) {
    qsts::external::state state = {{'A', 3}, {'B', 3}, {'C', 4}, {'D', 4}};
    auto pf1 = qsts::postfix("ABCD/+*");
    auto ex1 = qsts::convert(pf1);
    ASSERT_EQ(12.0, ex1.eval(state));

    auto pf2 = qsts::postfix("ABC+*D/");
    auto ex2 = qsts::convert(pf2);
    ASSERT_EQ(5.25, ex2.eval(state));
    
    auto pf3 = qsts::postfix("AB*CD/+");
    auto ex3 = qsts::convert(pf3);
    ASSERT_EQ(10.0, ex3.eval(state));
}

