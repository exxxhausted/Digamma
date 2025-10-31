#include "physics/objects/Detector.hpp"

namespace digamma::physics {

Detector::Detector(std::string name, geometry::Body body, Material material) :
    DGObject(std::move(name), std::move(body), std::move(material)){}

void Detector::prepareForNextPhoton() {
    delta_E_MeV_ = 0.0;
    if (current_idx_ == uninitialized) {
        current_idx_ = 0;
    }
    else {
        ++current_idx_;
        absorbed_energies_.emplace_back(delta_E_MeV_);
    }
}

void Detector::detectEnergyEmission(double MeV) { delta_E_MeV_ += MeV; }

const std::vector<double>& Detector::rawData() const { return absorbed_energies_; }

}
