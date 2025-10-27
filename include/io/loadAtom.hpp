#ifndef DIGAMMA_LOADATOM_HPP
#define DIGAMMA_LOADATOM_HPP

#include "physics/material/Atom.hpp"

#include <nlohmann/json.hpp>

namespace digamma::io {

physics::Atom loadAtom(const std::string& filename);

namespace internal {
    std::function<double(double)> parse_sigma(const nlohmann::json& obj);
    std::function<double(double)> parse_expr(const std::string& expr);
    double interpolate(const std::vector<std::pair<double,double>>& t, double E);
}

}

#endif // DIGAMMA_LOADATOM_HPP
