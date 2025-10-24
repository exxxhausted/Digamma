#ifndef DIGAMMA_SURFACEFACTORY_HPP
#define DIGAMMA_SURFACEFACTORY_HPP

#include "geometry/kernel/Surface.hpp"

namespace digamma::geometry {

enum class SphereApprox {
    Low,
    Medium,
    High,
    Ultra
};

class SurfaceFactory {
public:

    SurfaceFactory() = delete;
    static Surface createSphere(double radius = 1.0, SphereApprox quality = SphereApprox::Medium);
    static Surface createBox(double size_x = 1.0, double size_y = 1.0, double size_z = 1.0);
    static Surface createCube(double a);

private:

    static int sphereResolution(SphereApprox quality);

};

}

#endif // DIGAMMA_SURFACEFACTORY_HPP
