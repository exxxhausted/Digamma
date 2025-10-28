#ifndef DIGAMMA_MOLECULE_HPP
#define DIGAMMA_MOLECULE_HPP

#include "Atom.hpp"

namespace digamma::physics {

class Molecule {
public:
    struct Component {
        Atom atom;
        int count;
    };

    Molecule(const std::string&);
    Molecule(std::string name, double mass, std::vector<Component> components);
    const std::string& name() const;
    double mass() const;
    const std::vector<Component>& components() const;
    double sigmaPhoto(double MeV) const;
    double sigmaCompton(double MeV) const;
    double sigmaPair(double MeV) const;
    double sigmaTotal(double MeV) const;

private:

    std::string name_;
    double mass_;
    std::vector<Component> components_;
};

}

#endif // DIGAMMA_MOLECULE_HPP
