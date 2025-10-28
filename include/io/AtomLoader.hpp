#ifndef DIGAMMA_ATOMLOADER_HPP
#define DIGAMMA_ATOMLOADER_HPP

#include "physics/material/Atom.hpp"

#include <nlohmann/json.hpp>

namespace digamma::io {

class AtomLoader {
public:
    AtomLoader() = delete;
    static physics::Atom loadJSON(const std::string& filename);
private:
    static std::function<double(double)> parse_sigma(const nlohmann::json& obj);
    static std::function<double(double)> parse_expr(const std::string& expr);
    static double interpolate(const std::vector<std::pair<double,double>>& t, double E);
};

}

#endif // DIGAMMA_ATOMLOADER_HPP
