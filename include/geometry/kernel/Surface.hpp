#ifndef DIGAMMA_SURFACE_HPP
#define DIGAMMA_SURFACE_HPP

#include "geometry/interfaces/Serializable.hpp"
#include "geometry/interfaces/Transformable.hpp"

#include <utility>

namespace digamma::geometry {

class Surface : public Serializable,
                public Transformable
{
public:

    Surface(const Eigen::MatrixXd& vertices, const Eigen::MatrixXi& faces);

    void translate(const Vector& translation) override;
    void rotate(double angle_rad, const Vector& axis) override;
    void scale(double factor) override;

    void saveOBJ(const std::string& filename) const override;

    double area() const;

    auto data() const -> std::pair<const Eigen::MatrixXd&, const Eigen::MatrixXi&>;

    bool isClosed() const;

private:

    Eigen::MatrixXd vertices_;
    Eigen::MatrixXi faces_;

};


}

#endif // DIGAMMA_SURFACE_HPP
