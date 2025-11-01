#include <iostream>
#include <numbers>
#include <chrono>

#include "geometry/factories/SurfaceFactory.hpp"
#include "geometry/kernel/Body.hpp"
#include "io/writeOBJ.hpp"
#include "physics/material/Material.hpp"
#include "physics/objects/Detector.hpp"
#include "physics/objects/RadiationSource.hpp"
#include "application/Scene.hpp"

using namespace digamma;
using namespace geometry;
using namespace io;

#define E 0.662

int main() {
    try {

        auto start = std::chrono::high_resolution_clock::now();

        auto cube_surface = SurfaceFactory::createCube(100);
        auto sphere_surface = SurfaceFactory::createSphere(5, SphereApprox::Ultra);

        Body cube(cube_surface);
        Body sphere(sphere_surface);

        cube.translate(Vector(150,0,0));

        auto NaI = physics::Material("NaI");
        auto det = physics::Detector("det", cube, NaI);

        auto Cs_137 = physics::Material("Cs-137");
        auto rad = physics::RadiationSource("rad", sphere, NaI, E);

        auto scene = app::Scene();
        scene.addObj(std::make_shared<physics::DGObject>(det));
        scene.addObj(std::make_shared<physics::DGObject>(rad));

        int cnt = 0;
        for (int i = 0; i < 1e5; ++i) {
            if (i % 10000 == 0) std::cout << i / 10000 << std::endl;
            auto ph = rad.emitPhoton();
            if (scene.intersect(ph.ray()) != std::nullopt) cnt++;
        }

        saveOBJ({cube, sphere}, "view.obj");
        std::cout << cnt << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Execution time: " << duration.count() << " ms" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
