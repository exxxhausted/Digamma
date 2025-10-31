#include "geometry/kernel/Body.hpp"
#include "io/writeOBJ.hpp"

#include <igl/orientable_patches.h>
#include <igl/orient_outward.h>
#include <igl/winding_number.h>
#include <fstream>

namespace digamma::geometry {

Surface Body::orientOutward(const Surface& boundary) {
    const auto& [vertices, faces] = boundary.data();

    Eigen::VectorXi components;
    igl::orientable_patches(faces, components);

    Eigen::MatrixXi oriented_faces;
    Eigen::VectorXi flipped;
    igl::orient_outward(vertices, faces, components, oriented_faces, flipped);

    return Surface(vertices, oriented_faces);
}

double Body::manualVolume(const Eigen::MatrixXd& vertices, const Eigen::MatrixXi& faces) {
    double total_volume = 0.0;

    for (int i = 0; i < faces.rows(); ++i) {
        const Eigen::Vector3d& v0 = vertices.row(faces(i, 0));
        const Eigen::Vector3d& v1 = vertices.row(faces(i, 1));
        const Eigen::Vector3d& v2 = vertices.row(faces(i, 2));

        double volume = (v0.dot(v1.cross(v2))) / 6.0;
        total_volume += volume;
    }

    return total_volume;
}

Body::Body(const Surface& boundary) : boundary_(orientOutward(boundary)) {
    if (!boundary_.isClosed()) throw std::invalid_argument("Surface is not closed");
    if (volume() < 0) throw std::invalid_argument("Negative volume error");
}

void Body::translate(const Vector& translation) { boundary_.translate(translation); }

void Body::rotate(double angle, const Vector& axis) { boundary_.rotate(angle, axis); }

void Body::scale(double scale) { boundary_.scale(scale); }

std::size_t Body::saveOBJ(const std::string& filename, std::size_t offset) const {
    std::ofstream os(filename, std::ios::app);
    if (!os) throw std::runtime_error("Failed to save OBJ: " + filename);
    os << "o body" << "\n";
    const auto& [vertices, faces] = boundary_.data();
    return io::writeOBJ(vertices, faces, os, offset);
}

bool Body::contains(const Point& point) const {
    const auto& [vertices, faces] = boundary_.data();

    Eigen::MatrixXd points(1, 3);
    points.row(0) = point;

    Eigen::VectorXd winding_numbers;
    igl::winding_number(vertices, faces, points, winding_numbers);

    return winding_numbers(0) > 0.5;
}

double Body::area() const { return boundary_.area(); }

double Body::volume() const {
    const auto& [vertices, faces] = boundary_.data();
    return manualVolume(vertices, faces);
}

const Surface& Body::boundary() const { return boundary_; }

}