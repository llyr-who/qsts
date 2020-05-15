#pragma once

#include "io/postfix.hpp"
#include "io/state.hpp"
#include "io/token.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

namespace qsts {

//! Absorbs token to form a graph node
class node {
public:
    explicit node(const token& t) : t_(std::move(t)){};
    node() = delete;

    bool operator<(const node& n) const {
        if (left_ == nullptr && n.left_ == nullptr && right_ == nullptr &&
            n.right_ == nullptr) {
            // i.e if this node and the other are NOT
            // operations. More specifically they are
            // varianble or constant nodes.
            return t_->to_string() < n.t_->to_string();
        }
        return (t_->to_string() < n.t_->to_string() ||
                (t_->to_string() == n.t_->to_string() &&
                 left_->to_string() < n.left_->to_string()) ||
                (t_->to_string() == n.t_->to_string() &&
                 left_->to_string() == n.left_->to_string() &&
                 right_->to_string() < n.right_->to_string()));
    }
    void add_parent(const std::shared_ptr<node>& p) { parents_.push_back(p); }

    bool set_left_child(std::shared_ptr<node>&& lc) { left_ = lc; }
    bool set_right_child(std::shared_ptr<node>&& rc) { right_ = rc; }

    const std::vector<std::shared_ptr<node>>& parents() { return parents_; }
    const std::shared_ptr<node>& left() { return left_; }
    const std::shared_ptr<node>& right() { return right_; }

    double eval(const state& s) {
        if (t->type() == token::token_type::binary_operation) {
            if (t_->to_string() == "+") return right_->eval(s) + left_->eval(s);
            if (t_->to_string() == "-") return right_->eval(s) - left_->eval(s);
            if (t_->to_string() == "/") return right_->eval(s) / left_->eval(s);
            if (t_->to_string() == "*") return right_->eval(s) * left_->eval(s);
            return 0;
        }
        if (t_->type() == token::token_type::variable) {
            return s.at(t_.to_string());
        }
        if (t_->type() == token::token_type::constant) {
            return value();
        }
        return 0;
    }

    token::token_type type() { return t_.type(); }

private:
    double value() { return std::stod(t_.to_string()); }

    token t_;
    std::shared_ptr<node> left_;
    std::shared_ptr<node> right_;
    std::vector<std::shared_ptr<node>> parents_;
};

class graph_generator {
public:
    void add_node(std::shared_ptr<node> n) {
        auto it = unique_node_.insert(n);
        if (!it.second) {
            // i.e the node already exists;
            nodes_.push_back(it.first);
            return;
        }
        nodes_.push_back(n);
    }

    double operator[](const state& s) { return head_->eval(s); }

private:
    struct cmp {
        bool operator()(const std::shared_ptr<node>& a,
                        const std::shared_ptr<node>& b) {
            return *a < *b;
        }
    };
    std::set<std::shared_ptr<node>, cmp> unique_node_;
    std::list<std::shared_ptr<node>> nodes_;
}

struct graph {
    std::shared_ptr<node> head_;
};

//! convert postfix to expression
graph to_graph(postfix&& pfx) {
    std::stack<std::shared_ptr<node>> s;
    graph_generator g;
    auto pfx_tokens = pfx.move_tokens();
    for (auto& t : pfx_tokens) {
        if (t->type() != token::token_type::binary_operation) {
            // variable or constant
            s.push(std::make_shared<node>(std::move(t)));
            continue;
        }
        // else get the last two things on the stack
        auto op1 = s.top();
        s.pop();
        auto op2 = s.top();
        s.pop();
        // set them as children
        op1->add_parent(node(std::move(t));
        op2->add_parent(node(std::move(t));
        t->set_left_child(std::move(op1));
        t->set_right_child(std::move(op2));
        // push it back on the stack
        s.push(t);
    }
    return s.top();
}

}  // namespace qsts
