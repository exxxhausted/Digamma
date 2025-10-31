#include "physics/entities/Photon.hpp"

namespace digamma::physics {

Photon::Photon(geometry::Ray ray, double MeV) : ray_(std::move(ray)), photon_energy_MeV_(MeV) {}

double Photon::Energy() const { return photon_energy_MeV_; }

geometry::Ray Photon::ray() const { return ray_; }

}