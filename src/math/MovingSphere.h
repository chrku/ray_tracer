//
// Created by christoph on 30.07.19.
//

#ifndef RAY_TRACER_MOVINGSPHERE_H
#define RAY_TRACER_MOVINGSPHERE_H

#include "Hitable.h"

class MovingSphere : public Hitable {
public:
    template <typename MATERIAL_IMPL>
    MovingSphere(Vec3 center0, Vec3 center1, float t0, float t1, float r, MATERIAL_IMPL&& material)
        : center0_(center0), center1_(center1), t0_(t0), t1_(t1), radius_(r),
        material_(std::make_shared<MATERIAL_IMPL>(material)) {}
    bool hit(const Ray& r, float t_min, float t_max, HitRecord& record) const override {
        Vec3 origin_center = r.origin() - center(r.time());
        // Solve quadratic
        float a = dot(r.direction(), r.direction());
        float b = dot(origin_center, r.direction());
        float c = dot(origin_center, origin_center) - (radius_ * radius_);
        float discriminant = b * b - a * c;
        // Check discriminant
        if (discriminant > 0) {
            // Entry point
            float solution_1 = (-b - std::sqrt(discriminant)) / a;
            if (solution_1 < t_max && solution_1 > t_min) {
                record.t = solution_1;
                record.point = r.pointAtValue(record.t);
                record.normal = (record.point - center(r.time())) / radius_;
                record.material = material_;
                return true;
            }
            // Exit point
            float solution_2 = (-b + std::sqrt(discriminant)) / a;
            if (solution_2 < t_max && solution_2 > t_min) {
                record.t = solution_2;
                record.point = r.pointAtValue(record.t);
                record.normal = (record.point - center(r.time())) / radius_;
                record.material = material_;
                return true;
            }
        }
        return false;
    }
    bool bounding_box(float t0, float t1, AABB& box) const override {
        box = AABB::surroundingBox(
                AABB(center(t0) - Vec3(radius_, radius_, radius_),
                        center(t0) + Vec3(radius_, radius_, radius_)),
                AABB(center(t1) - Vec3(radius_, radius_, radius_),
                        center(t1) + Vec3(radius_, radius_, radius_)));
        return true;
    }

    float radius() const { return radius_; }
    Vec3 center(float t) const {
        float factor = ((t - t0_) / (t1_ - t0_));
        return center0_ + factor * (center1_ - center0_);
    }
private:
    // Center at t0, center at t1
    Vec3 center0_;
    Vec3 center1_;
    // Time values
    float t0_;
    float t1_;
    // Radius
    float radius_;
    // Material
    std::shared_ptr<Material> material_;
};


#endif //RAY_TRACER_MOVINGSPHERE_H
