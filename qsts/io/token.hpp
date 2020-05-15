#pragma once

#include <algorithm>
#include <cctype>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>

#include <iostream>

namespace qsts {

const std::string ops("(^-+*/)");
const std::map<std::string, int> priority_map = {{"(", -1}, {"^", 0}, {"-", 1},
                                                 {"+", 1},  {"*", 2}, {"/", 2}};

class token {
public:
    enum class token_type { variable, constant, binary_operation };
    enum class op_priority { bracket, other, division_multiplcation };

    token(std::string s) : s_(std::move(s)), t_(set_type()) {}
    token(char c) : s_(std::string(1, c)), t_(set_type()) {}
    token(const char* c_s) : s_(c_s), t_(set_type()) {}

    bool operator<(const token& t) const { return s_ < t.s_; }
    bool operator==(const token& t) const { return s_ == t.s_; }
    bool operator!=(const token& t) const { return s_ != t.s_; }

    double as_double() { return d_; }
    const std::string& as_string() const { return s_; }

    token_type type() const { return t_; }

    int priority() const {
        if (t_ != token_type::binary_operation) {
            return ops.size();
        }
        return priority_map.at(s_);
    }

    // ... stretching the notion of token.
    bool set_left_child(std::shared_ptr<token>&& lc) { left_ = lc; }
    bool set_right_child(std::shared_ptr<token>&& rc) { right_ = rc; }

    const std::shared_ptr<token>& left() { return left_; }
    const std::shared_ptr<token>& right() { return right_; }

private:
    token_type set_type() {
        if (s_.find_first_of(ops) != std::string::npos) {
            return token_type::binary_operation;
        }
        if (std::find_if(s_.begin(), s_.end(), [](unsigned char c) {
                return std::isalpha(c);
            }) == s_.end()) {
            d_ = std::stod(s_);
            return token_type::constant;
        }
        return token_type::variable;
    }

    std::string s_;
    double d_;
    token_type t_;

    // if binary op then these are non-nullptr
    std::shared_ptr<token> left_ = nullptr;
    std::shared_ptr<token> right_ = nullptr;
};

const std::map<char, token> ops_map = {{'(', token('(')}, {'+', token('+')},
                                       {'-', token('-')}, {'*', token('*')},
                                       {')', token(')')}, {'/', token('/')}};

template <typename T>
class token_container {
public:
    token_container() = default;

    void add_token(std::shared_ptr<token> t) {
        auto to_be_added = t;
        if(t->type() == token::token_type::variable) {
            auto it = unique_tks_.insert(t);
            if(!it.second) {
                to_be_added = *it.first;
            }
        }
        tks_.push_back(to_be_added);
    }

    std::list<std::shared_ptr<token>>&& move_tokens() {
        return std::move(tks_);
    }

    std::string as_string() const {
        std::string ts;
        for (const auto& t : tks_) {
            ts += t->as_string();
        }
        return ts;
    }
    
private:
    struct token_pointer_cmp {
        bool operator()(const std::shared_ptr<token>& a,
                        const std::shared_ptr<token>& b) const {
            return *a < *b;
        }
    };
    std::set<std::shared_ptr<token>, token_pointer_cmp> unique_tks_;
    std::list<std::shared_ptr<token>> tks_;
};

}  // namespace qsts
