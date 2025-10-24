#ifndef DIGAMMA_BODY_HPP
#define DIGAMMA_BODY_HPP

#include "geometry/kernel/Surface.hpp"

namespace digamma::geometry {

class Body : public Serializable,
             public Transformable
{
public:

    explicit Body(const Surface& boundary);

    void translate(const Vector& translation) override;
    void rotate(double angle_rad, const Vector& axis) override;
    void scale(double factor) override;

    void saveOBJ(const std::string& filename) const override;

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
