#include "types/infix.hpp"

#include "gtest/gtest.h"

TEST(convert, infix) {
    std::string exp_str1("A*B+C/D");
    auto if1 = qsts::exp::convert("A*B+C/D");
    ASSERT_EQ(if1.as_string(), exp_str1);

    std::string exp_str2("anthony+rose");
    auto if2 = qsts::exp::convert("anthony+rose");
    ASSERT_EQ(if2.as_string(), exp_str2);
    auto tks_if2 = if2.tokens();

    auto ant_it =
        std::find(tks_if2.begin(), tks_if2.end(), qsts::exp::token("anthony"));
    ASSERT_NE(ant_it, tks_if2.end());

    auto rose_it =
        std::find(tks_if2.begin(), tks_if2.end(), qsts::exp::token("rose"));
    ASSERT_NE(rose_it, tks_if2.end());
}

