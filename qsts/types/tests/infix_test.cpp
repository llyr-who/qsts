#include "types/infix.hpp"

#include "gtest/gtest.h"

TEST(convert, infix) {
    std::string expected("A*B+C/D");
    auto pf1 = qsts::exp::convert("A*B+C/D");
    ASSERT_EQ(pf1.as_string(), expected);
}

