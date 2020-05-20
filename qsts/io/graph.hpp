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
    explicit node(token t) : t_(std::move(t)){};
    explicit node(token t, token l, token r)
        : t_(std::move(t)),
          left_(std::make_shared<node>(l)),
          right_(std::make_shared<node>(r)) {}

    explicit node(node&& n)
        : t_(std::move(n.t_)),
          left_(std::move(n.left_)),
          right_(std::move(n.right_)) {}
    node() = delete;

    bool operator<(const node& n) const {
        if (left_ == nullptr && n.left_ == nullptr && right_ == nullptr &&
            n.right_ == nullptr) {
            // i.e if this node and the other are NOT
            // operations. More specifically they are
            // variable or constant nodes.
            return t_.to_string() < n.t_.to_string();
        }
        return (t_.to_string() < n.t_.to_string() ||
                (t_.to_string() == n.t_.to_string() &&
                 left_->t_.to_string() < n.left_->t_.to_string()) ||
                (t_.to_string() == n.t_.to_string() &&
                 left_->t_.to_string() == n.left_->t_.to_string() &&
                 right_->t_.to_string() < n.right_->t_.to_string()));
    }

    //! Checks that nodes have the same data.
    //! This does not mean they are the SAME node.
    bool operator==(const node& n) {
        if (t_ == n.t_ && left_->t_ == n.left_->t_ &&
            right_->t_ == n.right_->t_)
            return true;
        return false;
    }

    void add_parent(const std::shared_ptr<node>& p) { parents_.push_back(p); }

    bool set_left_child(std::shared_ptr<node>& lc) { left_ = lc; }
    bool set_right_child(std::shared_ptr<node>& rc) { right_ = rc; }

    const std::vector<std::shared_ptr<node>>& parents() { return parents_; }
    const std::shared_ptr<node>& left() { return left_; }
    const std::shared_ptr<node>& right() { return right_; }

    double eval(const state& s) {
        if (t_.type() == token::token_type::binary_operation) {
            if (t_.to_string() == "+") return right_->eval(s) + left_->eval(s);
            if (t_.to_string() == "-") return right_->eval(s) - left_->eval(s);
            if (t_.to_string() == "/") return right_->eval(s) / left_->eval(s);
            if (t_.to_string() == "*") return right_->eval(s) * left_->eval(s);
            return 0;
        }
        if (t_.type() == token::token_type::variable) {
            return s.at(t_.to_string());
        }
        if (t_.type() == token::token_type::constant) {
            return value();
        }
        return 0;
    }

    void print() {
        std::cout << "------------" << std::endl;
        std::cout << t_.to_string() << std::endl;
        std::cout << "------------" << std::endl;
        if (left_) {
            std::cout << left_ << std::endl;
            left_->print();
        }
        if (right_) {
            std::cout << right_ << std::endl;
            right_->print();
        }
    }

    token::token_type type() { return t_.type(); }
    const std::string& to_string() { return t_.to_string(); }

private:
    double value() { return std::stod(t_.to_string()); }

    token t_;
    std::shared_ptr<node> left_;
    std::shared_ptr<node> right_;
    std::vector<std::shared_ptr<node>> parents_;
};

class unique_stack {
public:
    void push(const std::shared_ptr<node>& n) {
        auto it = unique_node_.insert(n);
        if (!it.second) {
            // i.e the node already exists;
            s_.push(*it.first);
            return;
        }
        s_.push(n);
    }

    void pop() { s_.pop(); }
    std::shared_ptr<node>& top() { s_.top(); }

private:
    struct cmp {
        bool operator()(const std::shared_ptr<node>& a,
                        const std::shared_ptr<node>& b) {
            return *a < *b;
        }
    };
    std::set<std::shared_ptr<node>, cmp> unique_node_;
    std::stack<std::shared_ptr<node>> s_;
};

class graph {
public:
    graph(std::shared_ptr<qsts::node>&& n) : head_(n) {}
    double operator[](const state& s) { return head_->eval(s); }
    void print() {
        std::cout << head_ << std::endl;
        head_->print();
    }

    std::shared_ptr<node>&& get() { return std::move(head_); }

private:
    std::shared_ptr<node> head_;
};

//! convert postfix to expression
template <typename node>
graph to_graph(postfix&& pfx) {
    auto pfx_tokens = pfx.move_tokens();
    std::list<std::shared_ptr<node>> nodes;
    // move the tokens into nodes
    for (const auto& t : pfx_tokens) {
        nodes.push_back(std::make_shared<node>(std::move(*t)));
    }
    // now we have a graph generator which is essentially
    // a wrapped stack
    unique_stack s;
    for (auto& n : nodes) {
        if (n->type() != token::token_type::binary_operation) {
            // variable or constant
            s.push(n);
            continue;
        }
        auto op1 = s.top();
        s.pop();
        auto op2 = s.top();
        s.pop();

        op1->add_parent(n);
        op2->add_parent(n);
        n->set_left_child(op1);
        n->set_right_child(op2);
        s.push(n);
    }
    return graph(std::move(s.top()));
}

}  // namespace qsts
