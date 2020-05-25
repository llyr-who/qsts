
#include "qsts/autodiff/rad.hpp"

using namespace qsts;

using point = std::array<double, 3>;

int main() {
    auto e = rad::expression("x");

    point p({1.0, 1.0, 1.0});

    double eps = 0.01;

    for (std::size_t i = 0; i < 100; ++i) {
        // set state;
        state s = {{"x", p[0]}, {"y", p[1]}, {"z", p[2]}};
        // obtain gradient at state;
        auto g = e.grad(s);
        // convert to point;
        auto grad = point({g["x"], g["y"], g["z"]});
        // iterate;
        std::cout << grad[0] << " " << grad[1] << " " << grad[2] << std::endl;
        p[0] -= grad[0] * eps;
        p[1] -= grad[1] * eps;
        p[2] -= grad[2] * eps;

        std::cout << p[0] << " " << p[1] << " " << p[2] << std::endl;
    }
}
