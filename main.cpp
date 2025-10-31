#include <iostream>
#include <numbers>
#include <cassert>

#include "geometry/factories/SurfaceFactory.hpp"
#include "geometry/kernel/Body.hpp"
#include "io/writeOBJ.hpp"
#include "physics/material/Material.hpp"
#include "physics/objects/Detector.hpp"
#include "physics/objects/RadiationSource.hpp"

using namespace digamma;
using namespace geometry;
using namespace io;

#define E 0.662

int main() {
    try {
        auto cube_surface = SurfaceFactory::createCube(100);
        auto sphere_surface = SurfaceFactory::createSphere(5, SphereApprox::Ultra);

        Body cube(cube_surface);
        Body sphere(sphere_surface);

        cube.translate(Vector(150,0,0));

        auto NaI = physics::Material("NaI");
        auto det = physics::Detector("det", cube, NaI);

        auto Cs_137 = physics::Material("Cs-137");
        auto rad = physics::RadiationSource("rad", sphere, NaI, 0.662);

        int cnt = 0;
        for (int i = 0; i < 1e5; ++i) {
            if (i % 1000 == 0) std::cout << i / 1000 << std::endl;
            auto ph = rad.emitPhoton();
            if (det.body().boundary().intersect(ph.ray()) != std::nullopt) cnt++;
        }

        saveOBJ({cube, sphere}, "view.obj");
        std::cout << cnt << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
