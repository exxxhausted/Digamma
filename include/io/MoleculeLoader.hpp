#ifndef DIGAMMA_MOLECULELOADER_HPP
#define DIGAMMA_MOLECULELOADER_HPP

#include "physics/material/Molecule.hpp"

namespace digamma::io {

class MoleculeLoader {
public:
    MoleculeLoader() = delete;
    static physics::Molecule loadJSON(const std::string& filename);
};

}

#endif //DIGAMMA_MOLECULELOADER_HPP