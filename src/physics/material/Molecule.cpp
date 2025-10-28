#include "physics/material/Molecule.hpp"
#include "io/MoleculeLoader.hpp"

namespace digamma::physics {

Molecule::Molecule(const std::string& name) :
    Molecule(std::move(io::MoleculeLoader::loadJSON("./Database/Molecules/" + name + ".json"))) {}

Molecule::Molecule(std::string name, double mass, std::vector<Component> components) :
    name_(std::move(name)), mass_(mass), components_(std::move(components)) {}

const std::string& Molecule::name() const { return name_; }

double Molecule::mass() const { return mass_; }

const std::vector<Molecule::Component>& Molecule::components() const { return components_; }

double Molecule::sigmaPhoto(double MeV) const {
    double sum = 0.0;
    for (const auto& c : components_) sum += c.count * c.atom.sigmaPhoto(MeV);
    return sum;
}

double Molecule::sigmaCompton(double MeV) const {
    double sum = 0.0;
    for (const auto& c : components_) sum += c.count * c.atom.sigmaCompton(MeV);
    return sum;
}

double Molecule::sigmaPair(double MeV) const {
    double sum = 0.0;
    for (const auto& c : components_) sum += c.count * c.atom.sigmaPair(MeV);
    return sum;
}

double Molecule::sigmaTotal(double MeV) const {
    double sum = 0.0;
    for (const auto& c : components_) sum += c.count * c.atom.sigmaTotal(MeV);
    return sum;
}


}