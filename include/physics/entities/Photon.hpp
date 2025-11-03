#ifndef DIGAMMA_PHOTON_HPP
#define DIGAMMA_PHOTON_HPP

#include "geometry/kernel/Ray.hpp"

namespace digamma::physics {

class Photon {
public:

    Photon(geometry::Ray ray, double MeV);
    double energy() const;
    geometry::Ray ray() const;
    void move(double l);
    void setEnergy(double MeV);

private:

    double photon_energy_MeV_;
    geometry::Ray ray_;

};

}

#endif //DIGAMMA_PHOTON_HPP