#include "io/MoleculeLoader.hpp"
#include "io/MaterialLoader.hpp"

#include <fstream>
#include <nlohmann/json.hpp>

namespace digamma::io {

physics::Material MaterialLoader::loadJSON(const std::string& filename) {
    std::ifstream f(filename);
    if (!f) throw std::runtime_error("MaterialLoader: cannot open " + filename);
    nlohmann::json j;
    f >> j;

    double density = j.at("density");

    double fraction_sum = 0.0;
    std::vector<physics::Material::Component> comps;
    for (auto& c : j.at("composition")) {

        std::string molecule_name = c.at("molecule");
        double mass_fraction = c.at("mass_fraction");

        fraction_sum += mass_fraction;
        if(fraction_sum > 1.0) throw std::runtime_error("MaterialLoader: mass_fraction > 1.0");

        physics::Molecule molecule = MoleculeLoader::loadJSON("./Database/Molecules/" + molecule_name + ".json");
        comps.push_back({std::move(molecule), std::move(mass_fraction)});
    }

    return physics::Material(j.at("name"), density, std::move(comps));
}

}