#include "algo/convert.hpp"

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
    auto pf1 = qsts::postfix("ABCD/+*");
    auto ex1 = qsts::convert(pf1);
}

