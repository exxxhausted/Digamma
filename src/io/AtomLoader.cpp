#include "io/AtomLoader.hpp"

#include <exprtk.hpp>

namespace digamma::io {

physics::Atom AtomLoader::loadJSON(const std::string& filename) {
    std::ifstream f(filename);
    if (!f)
        throw std::runtime_error("AtomLoader: cannot open " + filename);
    nlohmann::json j;
    f >> j;

    std::string symbol = j.at("symbol");
    int Z = j.at("Z");
    double A = j.at("A");
    const auto& cs = j.at("cross_sections");
    const auto photo = parse_sigma(cs.at("photo"));
    const auto compton = parse_sigma(cs.at("compton"));
    const auto pair = parse_sigma(cs.at("pair"));

    return physics::Atom(symbol,
                            Z,
                            A,
                         photo,
                         compton,
                         pair);
}

std::function<double(double)> AtomLoader::parse_sigma(const nlohmann::json& obj) {
    std::string type = obj.at("type");

    if (type == "formula") {
        return parse_expr(obj.at("expr"));
    }
    else if (type == "table") {
        std::vector<std::pair<double,double>> table;
        for (auto& pair : obj.at("data"))
            table.emplace_back(pair[0], pair[1]);

        for (size_t i = 1; i < table.size(); ++i)
            if (table[i-1].first >= table[i].first)
                throw std::runtime_error(
                    "AtomLoader: energy table must be sorted strictly ascending.\n"
                    "Found non-increasing energy at index " + std::to_string(i)
                );

        return [table = std::move(table)](double E) {
            return interpolate(table, E);
        };
    }
    else {
        throw std::runtime_error("Unknown cross-section type: " + type);
    }
}

std::function<double(double)> AtomLoader::parse_expr(const std::string& expr) {
    auto E = std::make_shared<double>(0.0);
    auto sym = std::make_shared<exprtk::symbol_table<double>>();
    sym->add_variable("E", *E);
    sym->add_constants();

    auto expression = std::make_shared<exprtk::expression<double>>();
    expression->register_symbol_table(*sym);

    auto parser = std::make_shared<exprtk::parser<double>>();
    if (!parser->compile(expr, *expression))
        throw std::runtime_error("Invalid formula: " + expr);

    return [E, expression](double e) {
        *E = e;
        return expression->value();
    };
}

double AtomLoader::interpolate(const std::vector<std::pair<double,double>>& t, double E) {
    if (t.empty()) return 0.0;
    if (E <= t.front().first) return t.front().second;
    if (E >= t.back().first)  return t.back().second;

    auto it = std::upper_bound(t.begin(), t.end(), E,
        [](double e, const auto& p){ return e < p.first; });
    size_t i = std::distance(t.begin(), it);

    const auto& [E1, s1] = t[i-1];
    const auto& [E2, s2] = t[i];
    double f = (E - E1) / (E2 - E1);
    return s1 + f * (s2 - s1);
}

}