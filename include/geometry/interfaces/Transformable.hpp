#ifndef DIGAMMA_TRANSFORMABLE_HPP
#define DIGAMMA_TRANSFORMABLE_HPP

#include "geometry/kernel/Aliases.hpp"

namespace digamma::geometry {

class Transformable {
public:
    virtual ~Transformable() = default;
    virtual void translate(const Vector& translation) = 0;
    virtual void rotate(double angle_rad, const Vector& axis) = 0;
    virtual void scale(double factor) = 0;
};

}

#endif // DIGAMMA_TRANSFORMABLE_HPP
