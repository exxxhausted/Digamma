#ifndef DIGAMMA_SCENE_HPP
#define DIGAMMA_SCENE_HPP

#include "physics/objects/DGObject.hpp"

#include <vector>
#include <memory>

namespace digamma::app {

class Scene {
public:

    Scene() = default;
    Scene(std::vector<std::shared_ptr<physics::DGObject>>);
    Scene& addObj(std::shared_ptr<physics::DGObject>);
    Scene& removeObj(std::shared_ptr<physics::DGObject>);
    std::optional<geometry::IntersectionResult> intersect(const geometry::Ray&) const;

private:

    std::vector<std::shared_ptr<physics::DGObject>> objects_;

};

}

#endif // DIGAMMA_SCENE_HPP
