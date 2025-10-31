#ifndef DIGAMMA_RAY_HPP
#define DIGAMMA_RAY_HPP

#include "Aliases.hpp"

namespace digamma::geometry {

class Ray {
public:

    Ray(const Point&, const Vector&);
    Point pointAt(double) const;
    Point source() const;
    Vector direction() const;

private:
    Point source_;
    Vector direction_;
};

}

#endif //DIGAMMA_RAY_HPP