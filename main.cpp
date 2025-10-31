#include <iostream>
#include <numbers>

#include "geometry/factories/SurfaceFactory.hpp"
#include "geometry/kernel/Body.hpp"
#include "io/writeOBJ.hpp"
#include "physics/material/Material.hpp"

using namespace digamma;
using namespace geometry;
using namespace io;

#define E 0.662

int main() {
    try {

        auto NaI = physics::Material("NaI");

        std::cout << "Photo: " << NaI.sigmaPhoto(E) / NaI.sigmaTotal(E) << std::endl;
        std::cout << "Compton: " << NaI.sigmaCompton(E) / NaI.sigmaTotal(E) << std::endl;
        std::cout << "Pair: " << NaI.sigmaPair(E) / NaI.sigmaTotal(E) << std::endl;

        auto cube_surface = SurfaceFactory::createCube(100);
        auto sphere_surface = SurfaceFactory::createSphere(20, SphereApprox::Medium);

        Body cube(cube_surface);
        Body sphere(sphere_surface);

        cube.rotate(std::numbers::pi/4, Vector(0,0,1));
        sphere.translate(Vector(150,100,0));

        saveOBJ({cube, sphere}, "view.obj");
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
