#ifndef DIGAMMA_ACCELERATIONCACHE_HPP
#define DIGAMMA_ACCELERATIONCACHE_HPP

#include <igl/embree/EmbreeIntersector.h>

#include "geometry/kernel/Surface.hpp"

namespace digamma::geometry {

class AccelerationCache {
public:

    static AccelerationCache& instance();

    AccelerationCache(const AccelerationCache&) = delete;
    AccelerationCache& operator=(const AccelerationCache&) = delete;

    igl::embree::EmbreeIntersector& get(const Surface& surface);
    void invalidate(const Surface& surface);

private:

    AccelerationCache() = default;
    ~AccelerationCache() = default;

    std::unordered_map<const Surface*, std::unique_ptr<igl::embree::EmbreeIntersector>> cache_;

};

}

#endif //DIGAMMA_ACCELERATIONCACHE_HPP