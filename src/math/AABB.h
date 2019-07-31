//
// Created by christoph on 30.07.19.
//

#ifndef RAY_TRACER_AABB_H
#define RAY_TRACER_AABB_H

#include <cmath>

#include "Vec3.h"
#include "Ray.h"

class AABB {
public:
    AABB() = default;
    AABB(const Vec3& a, const Vec3& b) : min_(a), max_(b) {}
    Vec3 min() const { return min_; }
    Vec3 max() const { return max_; }

    bool hit (const Ray& r, float t_min, float t_max) const {
        float t0, t1;
        Vec3 min_origin = min_ - r.origin();
        Vec3 max_origin = max_ - r.origin();

        t0 = std::min(min_origin.x() / r.direction().x(), max_origin.x() / r.direction().x());
        t1 = std::max(min_origin.x() / r.direction().x(), max_origin.x() / r.direction().x());
        t_min = std::max(t0, t_min);
        t_max = std::min(t1, t_max);
        if (t_max <= t_min)
            return false;

        t0 = std::min(min_origin.y() / r.direction().y(), max_origin.y() / r.direction().y());
        t1 = std::max(min_origin.y() / r.direction().y(), max_origin.y() / r.direction().y());
        t_min = std::max(t0, t_min);
        t_max = std::min(t1, t_max);
        if (t_max <= t_min)
            return false;

        t0 = std::min(min_origin.z() / r.direction().z(), max_origin.z() / r.direction().z());
        t1 = std::max(min_origin.z() / r.direction().z(), max_origin.z() / r.direction().z());
        t_min = std::max(t0, t_min);
        t_max = std::min(t1, t_max);
        if (t_max <= t_min)
            return false;

        return true;
    }

    static AABB surroundingBox(const AABB& box0, const AABB& box1) {
        Vec3 smaller{std::min(box0.min().x(), box1.min().x()),
                     std::min(box0.min().y(), box1.min().y()),
                     std::min(box0.min().z(), box1.min().z())};
        Vec3 bigger{std::max(box0.max().x(), box1.max().x()),
                     std::max(box0.max().y(), box1.max().y()),
                     std::max(box0.max().z(), box1.max().z())};
        return {smaller, bigger};
    }
private:
    Vec3 min_;
    Vec3 max_;
};


#endif //RAY_TRACER_AABB_H
