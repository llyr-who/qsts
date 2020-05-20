#pragma once

#include "io/graph.hpp"
#include "io/postfix.hpp"
#include "io/state.hpp"

namespace qsts {

namespace rad {
class node : public qsts::node {
public:
    explicit node(qsts::token t) : qsts::node(t), grad_(0), value_(0) {}
    void grad(const qsts::state& s) {

    }
    double value_;
    double grad_;
};

class expression {
public:
    explicit expression(qsts::graph&& g) : g_(std::move(g)){};
    //
    void forward_pass(const state& s);

private:
    std::shared_ptr<node>&& get() {
        return std::move(std::static_pointer_cast<node>(g_.get()));
    }
    qsts::graph g_;
};

}  // namespace rad

rad::expression expression(std::string s) {
    return rad::expression(to_graph<rad::node>(std::move(to_postfix(s))));
}

double grad(rad::expression e, const state& s) {
    e.forward_pass();
    e.backward_pass();

    return 0;
}

}  // namespace qsts
