#ifndef DIGAMMA_SURFACE_HPP
#define DIGAMMA_SURFACE_HPP

#include <utility>
#include <optional>

#include "Aliases.hpp"
#include "Ray.hpp"
#include "geometry/intersection/IntersectionResult.hpp"

namespace digamma::geometry {

class Surface {
public:

    Surface(const Eigen::MatrixXd& vertices, const Eigen::MatrixXi& faces);

    void translate(const Vector& translation);
    void rotate(double angle_rad, const Vector& axis);
    void scale(double factor);

    std::size_t saveOBJ(const std::string& filename, std::size_t offset = 0) const;

    double area() const;

    auto data() const -> std::pair<const Eigen::MatrixXd&, const Eigen::MatrixXi&>;

    bool isClosed() const;

    std::optional<IntersectionResult> intersect(const Ray& ray) const;

private:

    Eigen::MatrixXd vertices_;
    Eigen::MatrixXi faces_;

};


}

#endif // DIGAMMA_SURFACE_HPP
