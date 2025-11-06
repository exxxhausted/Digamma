#include "physics/entities/Photon.hpp"

namespace digamma::physics {

Photon::Photon(geometry::Ray ray, double MeV) : ray_(std::move(ray)), photon_energy_MeV_(MeV) {}

double Photon::energy() const { return photon_energy_MeV_; }

geometry::Ray Photon::ray() const { return ray_; }

void Photon::move(double l) { ray_.moveSource(l); }

void Photon::setEnergy(double MeV) { photon_energy_MeV_ = MeV; }

void Photon::setDirection(geometry::Vector dir) { ray_ = geometry::Ray(ray_.source(), dir); }

}
