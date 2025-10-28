#include <iostream>
#include <numbers>

#include "geometry/factories/SurfaceFactory.hpp"
#include "geometry/kernel/Body.hpp"
#include "io/writeOBJ.hpp"
#include "physics/material/Material.hpp"

using namespace digamma;
using namespace geometry;
using namespace io;

int main() {
    try {

        auto NaI = physics::Material("NaI");

        std::cout << NaI.sigmaPhoto(0.662) / NaI.sigmaTotal(0.662) << std::endl;
        std::cout << NaI.sigmaCompton(0.662) / NaI.sigmaTotal(0.662) << std::endl;
        std::cout << NaI.sigmaPair(0.662) / NaI.sigmaTotal(0.662) << std::endl;

        // auto cube_surface = SurfaceFactory::createCube(100);
        // auto sphere_surface = SurfaceFactory::createSphere(20, SphereApprox::Medium);
        //
        // Body cube(cube_surface);
        // Body sphere(sphere_surface);
        //
        // cube.rotate(std::numbers::pi/4, Vector(0,0,1));
        // sphere.translate(Vector(150,100,0));
        //
        // writeOBJ({cube, sphere}, "view.obj");
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
