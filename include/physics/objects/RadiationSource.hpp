#ifndef DIGAMMA_RADIATIONSOURCE_HPP
#define DIGAMMA_RADIATIONSOURCE_HPP

#include "DGObject.hpp"
#include "physics/entities/Photon.hpp"

#include <random>

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

    //cache
    std::mt19937 gen_ = std::mt19937(std::random_device{}());
    double total_area_;
    std::uniform_real_distribution<double> dist_;
    std::vector<double> cumulative_areas_;
};

}

#endif //DIGAMMA_RADIATIONSOURCE_HPP