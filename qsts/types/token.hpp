#pragma once

#include <string>

namespace qsts {
namespace exp {

class token {
public:
    enum class type { variable, constant, binary_operation };
    token(std::string s) : t_(std::move(s)) {}
    type type() {
        // ...
    }
private:
    std::string t_;
};

class token_container {
public:
    explicit token_container(std::list<token>&& tks) : tks_(std::move(tks)) {}
    const std::list<token>& tokens() { return tks_; }

private:
    std::list<token> tks_;
};

int priority(const token& t) {
    
}


}  // namespace exp
}  // namespace qsts
