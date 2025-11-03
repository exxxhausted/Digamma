#include <iostream>
#include <cmath>
#include <chrono>
#include <random>

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
#define RAY_COUNT 100000
#define EPSILON 0.000001

bool isPointInCube(const Point& point, const Point& cube_center, double cube_size) {
    double half_size = cube_size / 2.0;
    return (point.x() >= cube_center.x() - half_size && point.x() <= cube_center.x() + half_size &&
            point.y() >= cube_center.y() - half_size && point.y() <= cube_center.y() + half_size &&
            point.z() >= cube_center.z() - half_size && point.z() <= cube_center.z() + half_size);
}

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
        auto rad = physics::RadiationSource("rad", sphere, Cs_137, E);

        auto scene = app::Scene();
        scene.addObj(std::make_shared<physics::DGObject>(det));
        scene.addObj(std::make_shared<physics::DGObject>(rad));

        auto gen = std::mt19937(std::random_device{}());
        auto dist = std::uniform_real_distribution<double>(0, 1);
        int cnt = 0;
        int absorbed_photons = 0;

        for (int i = 0; i < RAY_COUNT; ++i) {
            auto ph = rad.emitPhoton();
            auto intersection = scene.intersect(ph.ray());
            if (intersection != std::nullopt) {
                cnt++;
                ph.move(intersection->t + EPSILON);

                while (isPointInCube( ph.ray().source(), Point(150, 0, 0), 100) ) {
                    auto gamma = dist(gen);
                    auto sigma = det.material().sigmaTotal(ph.energy());

                    double lambda = -(1 / sigma) * log(gamma);
                    ph.move(lambda);
                    if (!isPointInCube( ph.ray().source(), Point(150, 0, 0), 100) ) break;

                    double sigma_photo = det.material().sigmaPhoto(ph.energy());
                    double sigma_compton = det.material().sigmaCompton(ph.energy());
                    double P_photo = sigma_photo / sigma;
                    double P_compton = sigma_compton / sigma;
                    double random_value = dist(gen);

                    if (random_value < P_photo) {
                        //Photo
                        absorbed_photons++;
                        det.detectPhotonAbsorption(ph.energy());
                        ph.setEnergy(0.0);
                        break;
                    }
                    else if (random_value < P_compton + P_photo) {
                        //Compton
                        double cos_theta = 1 - 2 * dist(gen);
                        double alpha = ph.energy() / 0.511;
                        double new_energy = ph.energy() / (1 + alpha * (1 - cos_theta));
                        double old_energy = ph.energy();

                        if (new_energy <= 0.0 + EPSILON) {
                            absorbed_photons++;
                            det.detectPhotonAbsorption(old_energy);
                            break;
                        }

                        ph.setEnergy(new_energy);
                    }
                    else {
                        //Pair
                    }
                }
            }
        }

        det.showHistogram();
        std::cout << "P_absorption: " << static_cast<double>(absorbed_photons) / cnt << std::endl;

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
