#include "application/Scene.hpp"

#include <algorithm>

namespace digamma::app {

Scene::Scene(std::vector<std::shared_ptr<physics::DGObject>> o) : objects_(std::move(o)) {}

Scene& Scene::addObj(std::shared_ptr<physics::DGObject> o) {
    objects_.push_back(o);
    return *this;
}

Scene& Scene::removeObj(std::shared_ptr<physics::DGObject> o) {
    auto it = std::find(objects_.begin(), objects_.end(), o);
    objects_.erase(it);
    return *this;
}

std::optional<geometry::IntersectionResult> Scene::intersect(const geometry::Ray& ray) const {
    std::optional<geometry::IntersectionResult> result = std::nullopt;

    for (const auto& o : objects_)
        if (auto current = o->intersect(ray); current.has_value())
            if (!result || current->t < result->t)
                result = std::move(current);

    return result;
}



}