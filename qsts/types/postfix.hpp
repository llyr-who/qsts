#pragma once

#include <list>

#include "qsts/types/token.hpp"

namespace qsts {
namespace exp {

class infix {
public:
    infix(std::string s) : tokenise(s){};
    std::string as_string();
    bool operator==(const nfix& nf) const {
        return nf.as_string() == *this.as_string();
    }

private:
    std::list<token> tokenise(std::string s);

    std::list<token> tks_;
};

void infix::tokenise(std::string s) {
    // remove spaces
    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
    size_t pos = 0;
    std::string t;
    while ((pos = s.find_first_of("+-/*()")) != std::string::npos) {
        tks_.push_back(token(s.substr(0, pos)));
        tks_.push_back(token(s[pos]);
        s.erase(0,pos+1);
    }
}

}  // namespace exp
}  // namespace qsts
