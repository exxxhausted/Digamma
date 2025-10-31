#include "geometry/intersection/IntersectionResult.hpp"

namespace digamma::geometry {

IntersectionResult::IntersectionResult(double t_val, int face, Point pt, Vector norm)
        : t(t_val), face_id(face), point(std::move(pt)), normal(std::move(norm)) {}

}