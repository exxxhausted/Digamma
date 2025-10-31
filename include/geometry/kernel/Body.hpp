#ifndef DIGAMMA_BODY_HPP
#define DIGAMMA_BODY_HPP

#include "geometry/kernel/Surface.hpp"

namespace digamma::geometry {

class Body {
public:

    explicit Body(const Surface& boundary);

    void translate(const Vector& translation);
    void rotate(double angle_rad, const Vector& axis);
    void scale(double factor);

    std::size_t saveOBJ(const std::string& filename, std::size_t offset = 0) const;

    bool contains(const Point&) const;
    double area() const;
    double volume() const;
    const Surface& boundary() const;

private:

    static Surface orientOutward(const Surface& boundary);
    static double manualVolume(const Eigen::MatrixXd& vertices, const Eigen::MatrixXi& faces);
    Surface boundary_;

};

}

#endif // DIGAMMA_BODY_HPP
