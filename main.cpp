#include <iostream>
#include <cmath>
#include <chrono>
#include <random>
#include <numbers>
#include <Eigen/Geometry>

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

#define PODGONIAN 0.85
#define E 0.662
#define RAY_COUNT 1000000
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

                bool photon_absorbed = false;

                while (isPointInCube(ph.ray().source(), Point(150, 0, 0), 100) && !photon_absorbed) {
                    
                    
                    auto gamma = dist(gen);
                    auto sigma = det.material().sigmaTotal(ph.energy());
                    double lambda = -(1 / sigma) * log(gamma);
                    ph.move(lambda);
                    
                    // Проверяем, остался ли фотон в детекторе после движения
                    if (!isPointInCube(ph.ray().source(), Point(150, 0, 0), 100)) {
                        break;
                    }

                    double sigma_photo = det.material().sigmaPhoto(ph.energy()) * PODGONIAN;
                    double sigma_compton = det.material().sigmaCompton(ph.energy());
                    double sigma_pair = det.material().sigmaPair(ph.energy());
                    double P_photo = sigma_photo / sigma;
                    double P_compton = sigma_compton / sigma;
                    double P_pair = sigma_pair / sigma;
                    double random_value = dist(gen);

                    if (random_value < P_photo) {
                        // Photoabsorption
                        det.detectPhotonAbsorption(ph.energy());
                        absorbed_photons++;
                        photon_absorbed = true;
                    }
                    else if (random_value < P_photo + P_compton) {
                        // Compton scattering
                        double alpha = ph.energy() / 0.511;
                        double random = dist(gen);
                        double cos_theta = 1.0 - (2.0 * alpha * random) / (1.0 + alpha * (1.0 - random));
                        double new_energy = ph.energy() / (1.0 + alpha * (1.0 - cos_theta));
                        double energy_loss = ph.energy() - new_energy;

                        // Обновляем направление
                        double phi = 2.0 * std::numbers::pi * dist(gen);
                        auto dir = ph.ray().direction();
                        
                        Vector perp;
                        if (std::abs(dir.dot(Eigen::Vector3d::UnitZ())) < 0.9) {
                            perp = dir.cross(Eigen::Vector3d::UnitZ()).normalized();
                        } else {
                            perp = dir.cross(Eigen::Vector3d::UnitX()).normalized();
                        }
                        
                        Vector new_dir = Eigen::AngleAxisd(acos(cos_theta), perp) * dir;
                        new_dir = Eigen::AngleAxisd(phi, dir) * new_dir;
                        
                        ph.setDirection(new_dir.normalized());

                        // Если энергия стала очень малой, считаем фотон поглощенным
                        if (new_energy <= 0.01) { // 10 keV порог
                            det.detectPhotonAbsorption(ph.energy());
                            absorbed_photons++;
                            photon_absorbed = true;
                            continue;
                        }

                        det.detectPhotonAbsorption(energy_loss);

                        ph.setEnergy(new_energy);
                    }
                    else if (random_value < P_photo + P_compton + P_pair) {
                        // Pair production
                        det.detectPhotonAbsorption(ph.energy());
                        absorbed_photons++;
                        photon_absorbed = true;
                    }
                }
            }
            
            // Прогресс
            if (i % (RAY_COUNT/10) == 0) {
                std::cout << "Processed " << i << "/" << RAY_COUNT << " photons" << std::endl;
            }
        }

        det.showHistogram(150);
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
