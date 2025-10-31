#ifndef DIGAMMA_DETECTOR_HPP
#define DIGAMMA_DETECTOR_HPP

#include "DGObject.hpp"

namespace digamma::physics {

constexpr std::size_t uninitialized = static_cast<std::size_t>(-1);

class Detector : public DGObject {
public:

    Detector(std::string name, geometry::Body body, Material material);
    void prepareForNextPhoton();
    void detectEnergyEmission(double MeV);
    const std::vector<double>& rawData() const;

private:

    double delta_E_MeV_ = 0.0;
    std::size_t current_idx_ = uninitialized;
    std::vector<double> absorbed_energies_;
};

}

#endif //DIGAMMA_DETECTOR_HPP