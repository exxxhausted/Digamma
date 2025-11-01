#include "physics/objects/RadiationSource.hpp"

#include <igl/per_face_normals.h>
#include <igl/barycenter.h>

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
    total_area_ = areas_.sum();
    dist_ = std::uniform_real_distribution<>(0, total_area_);

    cumulative_areas_.resize(areas_.size());
    cumulative_areas_[0] = areas_(0);
    for (int i = 1; i < areas_.size(); ++i) {
        cumulative_areas_[i] = cumulative_areas_[i-1] + areas_(i);
    }
}



std::size_t RadiationSource::chooseRandomTriangle() {
    double r = dist_(gen_);

    auto it = std::lower_bound(cumulative_areas_.begin(),
                              cumulative_areas_.end(),
                              r);
    return std::distance(cumulative_areas_.begin(), it);
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