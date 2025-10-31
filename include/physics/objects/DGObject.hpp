#ifndef DIGAMMA_DGOBJECT_HPP
#define DIGAMMA_DGOBJECT_HPP

#include "geometry/kernel/Body.hpp"
#include "physics/material/Material.hpp"

namespace digamma::physics {

class DGObject {
public:

    DGObject(std::string name, geometry::Body body, Material material);
    virtual ~DGObject() = default;
    const std::string& name() const;
    const geometry::Body& body() const;
    const Material& material() const;

protected:

    const std::string name_;
    geometry::Body body_;
    Material material_;

};

}

#endif //DIGAMMA_DGOBJECT_HPP