#pragma once

#include <algorithm>
#include <cctype>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

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

    token(const token& t) : s_(t.s_), t_(t.t_) {}
    token(token&& t) : s_(std::move(t.s_)), t_(std::move(t.t_)) {}

    bool operator<(const token& t) const { return s_ < t.s_; }
    bool operator==(const token& t) const { return s_ == t.s_; }
    bool operator!=(const token& t) const { return s_ != t.s_; }

    const std::string& to_string() const { return s_; }

    token_type type() const { return t_; }

    int priority() const {
        if (t_ != token_type::binary_operation) {
            return ops.size();
        }
        return priority_map.at(s_);
    }

private:
    token_type set_type() {
        if (s_.find_first_of(ops) != std::string::npos) {
            return token_type::binary_operation;
        }
        if (std::find_if(s_.begin(), s_.end(), [](unsigned char c) {
                return std::isalpha(c);
            }) == s_.end()) {
            return token_type::constant;
        }
        return token_type::variable;
    }

    std::string s_;
    token_type t_;
};

const std::map<char, token> ops_map = {{'(', token('(')}, {'+', token('+')},
                                       {'-', token('-')}, {'*', token('*')},
                                       {')', token(')')}, {'/', token('/')}};

template <typename T>
class token_container {
public:
    token_container() = default;

    void add_token(std::shared_ptr<token> t) {
        if (t->to_string() == "") return;
        tks_.push_back(t);
    }

    std::list<std::shared_ptr<token>>&& move_tokens() {
        return std::move(tks_);
    }

    std::string to_string() const {
        std::string ts;
        for (const auto& t : tks_) {
            ts += t->to_string();
        }
        return ts;
    }

private:
    std::list<std::shared_ptr<token>> tks_;
};

}  // namespace qsts
