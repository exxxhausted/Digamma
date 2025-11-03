#include "physics/objects/Detector.hpp"

#include <matplot/matplot.h>

namespace digamma::physics {

Detector::Detector(std::string name, geometry::Body body, Material material) :
    DGObject(std::move(name), std::move(body), std::move(material)){}

void Detector::detectPhotonAbsorption(double MeV) {
    absorbed_photons_.push_back(MeV);
}

void Detector::showHistogram(std::size_t bins) {
    matplot::hist(absorbed_photons_, bins);
    matplot::xlabel("Energy (MeV)");
    matplot::ylabel("Counts");
    matplot::title("Photon absorption histogram");
    matplot::show();
}

}
