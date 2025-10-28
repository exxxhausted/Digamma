#include "physics/material/Material.hpp"
#include "io/MaterialLoader.hpp"

#include <stdexcept>

#define N_A 6.02214076e23

namespace digamma::physics {

Material::Material(std::string name, double density, std::vector<Component> components) :
    name_(std::move(name)), density_(density), components_(std::move(components))
{
    double sum = 0.0;
    for (const auto& component : components_) sum += component.mass_fraction;
    if (sum > 1.0) throw std::runtime_error("Invalid material configuration");
}

Material::Material(const std::string& name) :
    Material(std::move(io::MaterialLoader::loadJSON("./Database/Materials/" + name + ".json"))) {}

double Material::density() const { return density_; }

const std::vector<Material::Component>& Material::components() const { return components_; }

const std::string& Material::name() const { return name_; }

double Material::sigmaPhoto(double MeV) const {
    double sigma = 0.0;
    for (const auto& c : components_) {
        double M = c.molecule.mass();
        sigma += c.mass_fraction * (N_A / M) * c.molecule.sigmaPhoto(MeV);
    }
    return sigma * density_;
}

double Material::sigmaCompton(double MeV) const {
    double sigma = 0.0;
    for (const auto& c : components_) {
        double M = c.molecule.mass();
        sigma += c.mass_fraction * (N_A / M) * c.molecule.sigmaCompton(MeV);
    }
    return sigma * density_;
}

double Material::sigmaPair(double MeV) const {
    double sigma = 0.0;
    for (const auto& c : components_) {
        double M = c.molecule.mass();
        sigma += c.mass_fraction * (N_A / M) * c.molecule.sigmaPair(MeV);
    }
    return sigma * density_;
}

double Material::sigmaTotal(double MeV) const {
    double sigma = 0.0;
    for (const auto& c : components_) {
        double M = c.molecule.mass();
        sigma += c.mass_fraction * (N_A / M) * c.molecule.sigmaTotal(MeV);
    }
    return sigma * density_;
}

}
