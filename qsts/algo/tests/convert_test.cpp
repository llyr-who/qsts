#include "algo/convert.hpp"

#include "gtest/gtest.h"

TEST(convert, infix_to_postfix) {
    qsts::infix e1 = "A*B+C/D";
    auto pf1 = qsts::convert(e1);
    ASSERT_EQ(pf1,"AB*CD/+");

    qsts::infix e2 = "A*(B+C)/D";
    auto pf2 = qsts::convert(e2);
    ASSERT_EQ(pf2, "ABC+*D/");
    std::cout << pf2 << std::endl;

    qsts::infix e3 = "A*(B+C/D)";
    auto pf3 = qsts::convert(e3);
    ASSERT_EQ(pf3, "ABCD/+*");
}

