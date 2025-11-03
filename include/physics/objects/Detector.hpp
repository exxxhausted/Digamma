#ifndef DIGAMMA_DETECTOR_HPP
#define DIGAMMA_DETECTOR_HPP

#include "DGObject.hpp"

#include <vector>

namespace digamma::physics {

class Detector : public DGObject {
public:

    Detector(std::string name, geometry::Body body, Material material);
    void detectPhotonAbsorption(double MeV);
    void showHistogram(std::size_t bins = 100);

private:

    std::vector<double> absorbed_photons_;
};

}

#endif //DIGAMMA_DETECTOR_HPP