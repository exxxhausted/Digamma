#ifndef DIGAMMA_MATERIALLOADER_HPP
#define DIGAMMA_MATERIALLOADER_HPP

#include "physics/material/Material.hpp"

namespace digamma::io {

class MaterialLoader {
public:
    MaterialLoader() = delete;
    static physics::Material loadJSON(const std::string& filename);
};

}

#endif //DIGAMMA_MATERIALLOADER_HPP