#include "geometry/kernel/Surface.hpp"
#include "io/writeOBJ.hpp"

#include <Eigen/Geometry>
#include <fstream>
#include <igl/doublearea.h>
#include <igl/boundary_facets.h>

namespace digamma::geometry {

Surface::Surface(const Eigen::MatrixXd& vertices, const Eigen::MatrixXi& faces) : vertices_(vertices), faces_(faces) {  }


void Surface::translate(const Vector& translation) {
    vertices_.rowwise() += translation.transpose();
}

void Surface::rotate(double angle_rad, const Vector& axis) {
    Eigen::Matrix3d rotation = Eigen::AngleAxisd(angle_rad, axis.normalized()).toRotationMatrix();
    vertices_ = (vertices_ * rotation.transpose()).eval();
}

void Surface::scale(double factor) { vertices_ *= factor; }

std::size_t Surface::saveOBJ(const std::string& filename, std::size_t offset) const {
    std::ofstream os(filename, std::ios::app);
    if (!os) throw std::runtime_error("Failed to save OBJ: " + filename);
    os << "o surface" << "\n";
    return io::writeOBJ(vertices_, faces_, os, offset);
}

double Surface::area() const {
    Eigen::VectorXd face_areas;
    igl::doublearea(vertices_, faces_, face_areas);
    return face_areas.sum() * 0.5;
}

auto Surface::data() const -> std::pair<const Eigen::MatrixXd&, const Eigen::MatrixXi&>
{ return {vertices_, faces_}; }

bool Surface::isClosed() const {
    Eigen::MatrixXi boundary_edges;
    igl::boundary_facets(faces_, boundary_edges);
    return boundary_edges.rows() == 0;
}

}
