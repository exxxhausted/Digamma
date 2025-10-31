#include "geometry/kernel/Ray.hpp"

namespace digamma::geometry {

Ray::Ray(const Point& source, const Vector& direction) : source_(source), direction_(direction) {}

Point Ray::pointAt(double l) const { return source_ + l * direction_; }

Point Ray::source() const { return source_; }

Vector Ray::direction() const { return direction_; }

}