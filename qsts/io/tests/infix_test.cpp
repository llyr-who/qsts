#include "io/infix.hpp"

#include "gtest/gtest.h"

TEST(as_infix, infix) {
    std::string exp_str1("A*B+C/D");
    auto if1 = qsts::to_infix("A*B+C/D");
    ASSERT_EQ(if1.to_string(), exp_str1);

    std::string exp_str2("anthony+rose");
    auto if2 = qsts::to_infix("anthony+rose");
    ASSERT_EQ(if2.to_string(), exp_str2);
    auto tks_if2 = if2.move_tokens();
}

