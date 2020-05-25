#include "io/expression.hpp"
#include "io/postfix.hpp"

#include "gtest/gtest.h"

#include <cstdlib>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>

using namespace qsts;
using namespace base;

/* while unique_stack is in expression.hpp, we test in here*/

TEST(unique_stack, basic) {
	unique_stack<node> s;
	s.push(std::make_shared<node>(token("A")));
	auto uis = s.unique_items();
	std::list<std::shared_ptr<node>> l;

	for (auto n : uis) {
		l.push_back(n);
	}

	ASSERT_EQ(l.size(), 1);

}

TEST(expression, eval) {
    std::string e0 = "(A+B)+A*(A+B)";
    auto g0 = base::expression<node>(std::move(to_postfix(e0)));
    qsts::state s0 = {{"A", 2.0}, {"B", 1.0}};
    qsts::state s1 = {{"A", 2.0}, {"B", 2.0}};
    qsts::state s2 = {{"A", 2.0}, {"B", 0.0}};
    qsts::state s3 = {{"A", -1.0}, {"B", 1.0}};
    qsts::state s4 = {{"A", 1.0}, {"B", 1.0}};
    ASSERT_EQ(g0[s0], 9.0);
    ASSERT_EQ(g0[s1], 12.0);
    ASSERT_EQ(g0[s2], 6.0);
    ASSERT_EQ(g0[s3], 0.0);
    ASSERT_EQ(g0[s4], 4.0);

	std::string e1 = "(A/B)";
	auto g1 = base::expression<node>(std::move(to_postfix(e1)));
	ASSERT_EQ(g1[s0], 2.0);
	ASSERT_EQ(g1[s1], 1.0);
	try {
		ASSERT_EQ(g1[s2], 0.0);
		ASSERT_TRUE(false);
	}
	catch (std::invalid_argument & e) {
		ASSERT_TRUE(true);
	}
	ASSERT_EQ(g1[s3], -1.0);
	ASSERT_EQ(g1[s4], 1.0);

	std::string e2 = "A - B";
	auto g2 = base::expression<node>(std::move(to_postfix(e2)));
	ASSERT_EQ(g2[s0], 1.0);
	ASSERT_EQ(g2[s1], 0.0);
	ASSERT_EQ(g2[s2], 2.0);
	ASSERT_EQ(g2[s3], -2.0);
	ASSERT_EQ(g2[s4], 0.0);

}

void fill_count_map(std::map<std::shared_ptr<node>, int>& nodes,
                    const std::shared_ptr<node>& head) {
    auto it_h = nodes.insert(std::make_pair(head, 1));
    if (!it_h.second) {
        it_h.first->second++;
    }

    if (head->left() != nullptr) {
        fill_count_map(nodes, head->left());
    }
    if (head->right() != nullptr) {
        fill_count_map(nodes, head->right());
    }
}

auto unique_tester(const std::shared_ptr<node>& head) {
    std::map<std::shared_ptr<node>, int> nodes;
    fill_count_map(nodes, head);
    return nodes;
}

class test_expression : public base::expression<node> {
public:
    test_expression(postfix&& pfx) : base::expression<node>(std::move(pfx)) {}
    std::shared_ptr<node> get() { return head_; }
};

TEST(expression, unique) {
    std::string e1 = "(A+B)+A*(A+B)";
    auto g0 = test_expression(to_postfix(e1));
    // gets the shared pointer of the head of the expression
    auto nodes = unique_tester(g0.get());
    node a_plus_b = node(token("+"), token("A"), token("B"));
    for (const auto& n : nodes) {
        if (n.first->to_string() == "A") {
            ASSERT_EQ(n.second, 3);
            continue;
        }
        if (n.first->to_string() == "B") {
            ASSERT_EQ(n.second, 2);
            continue;
        }
        if (*n.first == a_plus_b) {
            ASSERT_EQ(n.second, 2);
            continue;
        }
    }
}