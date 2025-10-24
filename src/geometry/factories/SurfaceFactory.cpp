#include "geometry/factories/SurfaceFactory.hpp"

#include <numbers>

namespace digamma::geometry {

int SurfaceFactory::sphereResolution(SphereApprox quality) {
    switch (quality) {
        case SphereApprox::Low:    return 8;
        case SphereApprox::Medium: return 16;
        case SphereApprox::High:   return 32;
        case SphereApprox::Ultra:  return 64;
        default: return 16;
    }
}

Surface SurfaceFactory::createSphere(double radius, SphereApprox quality) {
    int segments = sphereResolution(quality);

    int vertex_count = segments * (segments - 1) + 2;
    int face_count = segments * (segments - 2) * 2 + segments * 2;

    Eigen::MatrixXd vertices(vertex_count, 3);
    Eigen::MatrixXi faces(face_count, 3);

    int vertex_index = 0;

    // Северный полюс (индекс 0)
    vertices.row(vertex_index++) << 0, 0, radius;

    // Промежуточные кольца (исключая полюса)
    for (int i = 1; i < segments; ++i) {
        double theta = std::numbers::pi * i / segments;
        for (int j = 0; j < segments; ++j) {
            double phi = 2 * std::numbers::pi * j / segments;

            vertices(vertex_index, 0) = radius * std::sin(theta) * std::cos(phi);
            vertices(vertex_index, 1) = radius * std::sin(theta) * std::sin(phi);
            vertices(vertex_index, 2) = radius * std::cos(theta);
            vertex_index++;
        }
    }

    // Южный полюс (последний индекс)
    vertices.row(vertex_index++) << 0, 0, -radius;

    int face_index = 0;

    for (int j = 0; j < segments; ++j) {
        int next_j = (j + 1) % segments;
        faces.row(face_index++) << 0, 1 + j, 1 + next_j;
    }

    for (int i = 0; i < segments - 2; ++i) {
        int current_ring_start = 1 + i * segments;
        int next_ring_start = 1 + (i + 1) * segments;

        for (int j = 0; j < segments; ++j) {
            int next_j = (j + 1) % segments;

            int v00 = current_ring_start + j;
            int v01 = current_ring_start + next_j;
            int v10 = next_ring_start + j;
            int v11 = next_ring_start + next_j;

            faces.row(face_index++) << v00, v10, v01;
            faces.row(face_index++) << v01, v10, v11;
        }
    }

    int last_ring_start = 1 + (segments - 2) * segments;
    int south_pole = vertex_count - 1;

    for (int j = 0; j < segments; ++j) {
        int next_j = (j + 1) % segments;
        faces.row(face_index++) << south_pole, last_ring_start + next_j, last_ring_start + j;
    }

    return Surface(vertices, faces);
}

Surface SurfaceFactory::createBox(double size_x, double size_y, double size_z) {
    Eigen::MatrixXd vertices(8, 3);
    Eigen::MatrixXi faces(12, 3);

    double sx = size_x / 2.0, sy = size_y / 2.0, sz = size_z / 2.0;
    vertices << -sx, -sy, -sz,
                 sx, -sy, -sz,
                 sx,  sy, -sz,
                -sx,  sy, -sz,
                -sx, -sy,  sz,
                 sx, -sy,  sz,
                 sx,  sy,  sz,
                -sx,  sy,  sz;

    faces << 0, 1, 2,  0, 2, 3,
             4, 5, 6,  4, 6, 7,
             0, 1, 5,  0, 5, 4,
             2, 3, 7,  2, 7, 6,
             0, 3, 7,  0, 7, 4,
             1, 2, 6,  1, 6, 5;

    return Surface(vertices, faces);
}

Surface SurfaceFactory::createCube(double a) { return createBox(a, a, a); }

}
