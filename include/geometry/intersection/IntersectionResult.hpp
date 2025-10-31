#ifndef DIGAMMA_INTERSECTIONRESULT_HPP
#define DIGAMMA_INTERSECTIONRESULT_HPP

#include "geometry/kernel/Aliases.hpp"

namespace digamma::geometry {

struct IntersectionResult {
    double t;
    int face_id;
    Point point;
    Vector normal;

    IntersectionResult(double t_val, int face, const Point pt, Vector norm);
};

}

#endif //DIGAMMA_INTERSECTIONRESULT_HPP