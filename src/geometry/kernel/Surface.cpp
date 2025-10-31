#include "geometry/kernel/Surface.hpp"
#include "io/writeOBJ.hpp"
#include "geometry/intersection/AccelerationCache.hpp"

#include <Eigen/Geometry>
#include <fstream>
#include <igl/doublearea.h>
#include <igl/boundary_facets.h>
#include <igl/Hit.h>

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

std::optional<IntersectionResult> Surface::intersect(const Ray& ray) const {
    auto& intersector = AccelerationCache::instance().get(*this);
    igl::Hit<float> hit;
    Eigen::Vector3f origin = ray.source().cast<float>();
    Eigen::Vector3f dir    = ray.direction().cast<float>();
    if (intersector.intersectRay(origin, dir, hit)) {
        Point point = ray.pointAt(hit.t);

        const auto& face = faces_.row(hit.id);
        Eigen::Vector3d v0 = vertices_.row(face[0]);
        Eigen::Vector3d v1 = vertices_.row(face[1]);
        Eigen::Vector3d v2 = vertices_.row(face[2]);
        Vector normal = (v1 - v0).cross(v2 - v0).normalized();

        return IntersectionResult(hit.t, hit.id, point, normal);
    }

    return std::nullopt;
}

}
