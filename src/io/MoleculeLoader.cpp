#include "io/MoleculeLoader.hpp"
#include "io/AtomLoader.hpp"

#include <nlohmann/json.hpp>
#include <fstream>

namespace digamma::io {

physics::Molecule MoleculeLoader::loadJSON(const std::string& filename) {
    std::ifstream f(filename);
    if (!f) throw std::runtime_error("MoleculeLoader: cannot open " + filename);
    nlohmann::json j;
    f >> j;

    std::vector<physics::Component> comps;
    for (auto& c : j.at("composition")) {

        std::string elem = c.at("element");
        int count = c.at("count");

        physics::Atom atom = AtomLoader::loadJSON("./Database/Atoms/" + elem + ".json");
        comps.push_back({std::move(atom), std::move(count)});
    }

    return physics::Molecule{j.at("name"), std::move(comps)};
}

}