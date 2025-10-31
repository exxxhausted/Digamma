#ifndef DIGAMMA_PHOTON_HPP
#define DIGAMMA_PHOTON_HPP

#include "geometry/kernel/Ray.hpp"

namespace digamma::physics {

class Photon {
public:

    Photon(geometry::Ray ray, double MeV);
    double Energy() const;
    geometry::Ray ray() const;

private:

    double photon_energy_MeV_;
    geometry::Ray ray_;

};

}

#endif //DIGAMMA_PHOTON_HPP