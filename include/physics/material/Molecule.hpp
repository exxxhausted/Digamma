#ifndef DIGAMMA_MOLECULE_HPP
#define DIGAMMA_MOLECULE_HPP

#include "Atom.hpp"

namespace digamma::physics {

struct Component {
    Atom atom;
    int count;
};

class Molecule {
public:
    Molecule(const std::string&);
    Molecule(std::string name, std::vector<Component> components);
    const std::string& name() const;
    const std::vector<Component>& components() const;
    double sigmaPhoto(double E) const;
    double sigmaCompton(double E) const;
    double sigmaPair(double E) const;
    double sigmaTotal(double E) const;
private:
    std::string name_;
    std::vector<Component> components_;
};

}

#endif // DIGAMMA_MOLECULE_HPP
