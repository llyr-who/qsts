#pragma once
#include <string>
namespace qsts {
class token {
public:
    token(std::string s) : t_(std::move(s)) {}

private:
    std::string t_;
};
}  // namespace qsts
