#include <iostream>
#include <numbers>

#include "geometry/factories/SurfaceFactory.hpp"
#include "geometry/kernel/Body.hpp"
#include "io/writeOBJ.hpp"
#include "io/loadAtom.hpp"
#include "physics/material/Atom.hpp"

using namespace digamma;
using namespace geometry;
using namespace io;

int main() {
    try {

        auto I = physics::Atom("I");
        std::cout << I.sigma_compton(0.662);

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
