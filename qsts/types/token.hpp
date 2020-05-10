#pragma once

#include <algorithm>
#include <cctype>
#include <list>
#include <map>
#include <stdexcept>
#include <string>

namespace qsts {
namespace exp {

const std::string ops("(^-+*/");
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
    explicit token_container(std::list<token>&& tks) : tks_(std::move(tks)) {}

    const std::list<token>& tokens() const { return tks_; }
    std::string as_string() const {
        std::string ts;
        for (const auto& t : tks_) {
            ts += t.as_string();
        }
        return ts;
    }

private:
    std::list<token> tks_;
};

auto tokenise(std::string s) {
    std::list<token> ts;
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    size_t pos = 0;
    std::string t;
    while ((pos = s.find_first_of("+-/*()")) != std::string::npos) {
        ts.push_back(token(s.substr(0, pos)));
        ts.push_back(token(s[pos]));
        s.erase(0, pos + 1);
    }
    if (s.size() > 0) {
        ts.push_back(token(s));
    }
    return std::move(ts);
}

}  // namespace exp
}  // namespace qsts
