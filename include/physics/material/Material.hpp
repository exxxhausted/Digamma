#ifndef DIGAMMA_MATERIAL_HPP
#define DIGAMMA_MATERIAL_HPP

#include "Molecule.hpp"

namespace digamma::physics {

class Material {
public:

    struct Component {
        Molecule molecule;
        double mass_fraction;
    };

    Material(const std::string& name);
    Material(std::string name, double density, std::vector<Component> components);
    double density() const;
    const std::vector<Component>& components() const;
    const std::string& name() const;
    double sigmaPhoto(double MeV) const;
    double sigmaCompton(double MeV) const;
    double sigmaPair(double MeV) const;
    double sigmaTotal(double MeV) const;

private:

    std::string name_;
    double density_;
    std::vector<Component> components_;

};

}

#endif //DIGAMMA_MATERIAL_HPP