#pragma once

#include <algorithm>
#include <cctype>
#include <list>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include <iostream>

namespace qsts {
namespace exp {

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

    bool operator==(const token& t) const { return s_ == t.s_; }
    bool operator!=(const token& t) const { return s_ != t.s_; }

    const std::string& as_string() const { return s_; }

    token_type type() const { return t_; }

    int priority() const {
        if (t_ != token_type::binary_operation) {
            return ops.size();
        }
        return priority_map.at(s_);
    }

    bool set_left_child(std::shared_ptr<token>&& lc) { left_ = lc; }
    bool set_right_child(std::shared_ptr<token>&& rc) { right_ = rc; }

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
    explicit token_container(std::list<std::shared_ptr<token>>&& tks)
        : tks_(std::move(tks)) {}

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
    std::list<std::shared_ptr<token>> tks_;
};

auto tokenise(std::string s) {
    std::list<std::shared_ptr<token>> ts;
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    size_t pos = 0;
    std::string t;
    while ((pos = s.find_first_of("+-/*()")) != std::string::npos) {
        ts.push_back(std::make_shared<token>(s.substr(0, pos)));
        ts.push_back(std::make_shared<token>(s[pos]));
        s.erase(0, pos + 1);
    }
    if (s.size() > 0) {
        ts.push_back(std::make_shared<token>(s));
    }
    return std::move(ts);
}

}  // namespace exp
}  // namespace qsts
