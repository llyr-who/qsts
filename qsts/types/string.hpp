#pragma once

#include <string>

namespace qsts {

namespace type {
struct infix {};
struct postfix {};
}  // namespace type

template <typename format>
class string {
public:
    string(std::string s) : value_(std::move(s)){};
    const std::string& value() const { return value_; }
    bool operator==(const string& s) const {
        return s.value_ == value_;
    }
private:
    std::string value_;
};

using infix = string<type::infix>;
using postfix = string<type::postfix>;

}  // namespace qsts
