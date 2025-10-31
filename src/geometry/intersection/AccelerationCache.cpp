#include "geometry/intersection/AccelerationCache.hpp"

namespace digamma::geometry {

AccelerationCache& AccelerationCache::instance() {
    static AccelerationCache instance;
    return instance;
}

igl::embree::EmbreeIntersector& AccelerationCache::get(const Surface& surface) {
    auto it = cache_.find(&surface);
    if (it != cache_.end()) {
        return *it->second;
    }

    const auto& [vertices, faces] = surface.data();
    auto intersector = std::make_unique<igl::embree::EmbreeIntersector>();

    Eigen::MatrixXf V = vertices.cast<float>();

    intersector->init(V, faces);

    auto& result = *intersector;
    cache_.emplace(&surface, std::move(intersector));
    return result;
}

void AccelerationCache::invalidate(const Surface& surface) { cache_.erase(&surface); }

}