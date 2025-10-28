#include "physics/material/Molecule.hpp"
#include "io/MoleculeLoader.hpp"

namespace digamma::physics {

Molecule::Molecule(const std::string& name) :
    Molecule(std::move(io::MoleculeLoader::loadJSON("./Database/Molecules/" + name + ".json"))) {}

Molecule::Molecule(std::string name, std::vector<Component> components) :
    name_(std::move(name)), components_(std::move(components)) {}

const std::string& Molecule::name() const { return name_; }

const std::vector<Component>& Molecule::components() const { return components_; }

double Molecule::sigmaPhoto(double E) const {
    double sum = 0.0;
    size_t count_sum = 0;
    for (const auto& c : components_) {
        sum += c.count * c.atom.sigmaPhoto(E);
        count_sum += c.count;
    }
    return count_sum ? sum / count_sum : 0.0;
}

double Molecule::sigmaCompton(double E) const {
    double sum = 0.0;
    size_t count_sum = 0;
    for (const auto& c : components_) {
        sum += c.count * c.atom.sigmaCompton(E);
        count_sum += c.count;
    }
    return count_sum ? sum / count_sum : 0.0;
}

double Molecule::sigmaPair(double E) const {
    double sum = 0.0;
    size_t count_sum = 0;
    for (const auto& c : components_) {
        sum += c.count * c.atom.sigmaPair(E);
        count_sum += c.count;
    }
    return count_sum ? sum / count_sum : 0.0;
}

double Molecule::sigmaTotal(double E) const {
    double sum = 0.0;
    size_t count_sum = 0;
    for (const auto& c : components_) {
        sum += c.count * c.atom.sigmaTotal(E);
        count_sum += c.count;
    }
    return count_sum ? sum / count_sum : 0.0;
}


}