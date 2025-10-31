#ifndef DIGAMMA_RADIATIONSOURCE_HPP
#define DIGAMMA_RADIATIONSOURCE_HPP

#include "DGObject.hpp"
#include "physics/entities/Photon.hpp"

namespace digamma::physics {

class RadiationSource : public DGObject {
public:

    RadiationSource(std::string name, geometry::Body body, Material material, double photon_energy_MeV);
    Photon emitPhoton();

private:

    const double photon_energy_MeV_;

    Eigen::MatrixXd normals_;
    Eigen::MatrixXd centers_;
    Eigen::MatrixXd areas_;


    std::size_t chooseRandomTriangle();

};

}

#endif //DIGAMMA_RADIATIONSOURCE_HPP