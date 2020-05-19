#include "io/postfix.hpp"

#include "gtest/gtest.h"

TEST(to_postfix, postfix) {
    std::string exp_str1("AB*CD/+");
    auto pf1 = qsts::to_postfix("A*B+C/D");
    ASSERT_EQ(pf1.to_string(), exp_str1);

    std::cout << "---- DEBUG" << std::endl;
    auto pf2 = qsts::to_postfix("A+A+A");
    auto pf2_tokens = pf2.move_tokens();

    auto A = pf2_tokens.front();
    int count = 0;
    for (const auto& t : pf2_tokens) {
        if (t == A) {
            ++count;
        }

        std::cout << t << std::endl;
    }
    std::cout << count << std::endl;
}

