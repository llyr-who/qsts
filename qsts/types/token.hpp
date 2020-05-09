#pragma once

#include <algorithm>
#include <cctype>
#include <list>
#include <string>

namespace qsts {
namespace exp {

const std::string ops("(^-+*/");

class token {
public:
    enum class token_type { variable, constant, binary_operation };

    token(std::string s) : s_(std::move(s)), t_(set_type()) {}
    token(char c) : s_(std::string(1, c)), t_(set_type()) {}
    token(const char* c_s) : s_(c_s), t_(set_type()) {}

    const std::string& as_string() const { return s_; }

    token_type type() const { return t_; }

    int priority() {
        auto pos = s_.find_first_of(ops);
        if (pos != std::string::npos) {
            return pos;
        }
        return ops.size();
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

template <typename T>
class token_container {
public:
    explicit token_container(std::list<token>&& tks) : tks_(std::move(tks)) {}
    const std::list<token>& tokens() { return tks_; }
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

}  // namespace exp
}  // namespace qsts
