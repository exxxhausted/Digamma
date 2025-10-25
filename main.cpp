#include <iostream>


#include "geometry/factories/SurfaceFactory.hpp"
#include "geometry/kernel/Body.hpp"
#include "io/writeOBJ.hpp"

int main() {

    try {
        auto bubu_src = digamma::geometry::SurfaceFactory::createCube(100);
        auto bebe_src = digamma::geometry::SurfaceFactory::createSphere(10, digamma::geometry::SphereApprox::Low);

        digamma::geometry::Body bubu(bubu_src);
        digamma::geometry::Body bebe(bebe_src);

        bubu.rotate(3.1415/4, digamma::geometry::Vector(0,0,1));
        bubu.translate(digamma::geometry::Vector(150,0,0));

        bebe.saveOBJ("view_bebe.obj");
        bubu.saveOBJ("view_bubu.obj");
        digamma::io::writeOBJ({bubu, bebe}, "view.obj");

    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
