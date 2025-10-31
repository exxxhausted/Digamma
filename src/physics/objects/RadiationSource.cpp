#include "physics/objects/RadiationSource.hpp"

#include <igl/per_face_normals.h>
#include <igl/barycenter.h>
#include <random>

namespace digamma::physics {

RadiationSource::RadiationSource(std::string name,
                                 geometry::Body body,
                                 Material material,
                                 double photon_energy_MeV) :
    DGObject(std::move(name), std::move(body), std::move(material)),
    photon_energy_MeV_(photon_energy_MeV)
{
    const auto& [V, F] = body_.boundary().data();

    igl::per_face_normals(V, F, normals_);
    igl::barycenter(V, F, centers_);
    igl::doublearea(V, F, areas_);
    areas_ *= 0.5;
}

std::size_t RadiationSource::chooseRandomTriangle() {
    static std::mt19937 gen(std::random_device{}());
    double total_area = areas_.sum();
    std::uniform_real_distribution dist(0.0, total_area);
    double r = dist(gen);

    double accum = 0.0;
    for (std::size_t i = 0; i < areas_.size(); ++i) {
        accum += areas_(i);
        if (r <= accum)
            return i;
    }

    return areas_.size() - 1;
}

Photon RadiationSource::emitPhoton() {
    std::size_t id = chooseRandomTriangle();
    geometry::Point source(centers_(id, 0), centers_(id, 1), centers_(id, 2));
    geometry::Vector direction(normals_(id, 0), normals_(id, 1), normals_(id, 2));
    geometry::Ray ray(source, direction);
    ray.moveSource(0.0001);
    return Photon(ray, photon_energy_MeV_);
}



}