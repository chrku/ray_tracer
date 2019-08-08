//
// Created by christoph on 08.08.19.
//

#ifndef RAY_TRACER_AARECT_H
#define RAY_TRACER_AARECT_H


#include "Hitable.h"

class AARect : public Hitable {
public:
    template <typename MATERIAL_IMPL>
    AARect(float x0, float x1, float y0, float y1, float z, MATERIAL_IMPL&& material)
        : x0_(x0), x1_(x1), y0_(y0), y1_(y1), z_(z), material_(std::make_shared<MATERIAL_IMPL>(material))
    {}

    bool hit(const Ray& r, float t0, float t1, HitRecord& record) const override {
        float t = (z_ - r.origin().z()) / r.direction().z();
        if (t < t0 || t > t1)
            return false;
        float x = r.origin().x() + t * r.direction().x();
        float y = r.origin().y() + t * r.direction().y();
        if (x < x0_ || x > x1_ || y < y0_ || y > y1_)
            return false;

        record.u = (x - x0_) / (x1_ - x0_);
        record.v = (y - y0_) / (y1_ - y0_);
        record.t = t;
        record.material = material_;
        record.point = r.pointAtValue(t);
        record.normal = Vec3(0.f, 0.f, 1.f);
        return true;
    }
    bool boundingBox(float f0, float t1, AABB& box) const override {
        box = AABB(Vec3(x0_, y0_, z_ - 0.00001f), Vec3(x1_, y1_, z_ + 0.00001f));
        return true;
    }
private:
    float x0_;
    float x1_;
    float y0_;
    float y1_;
    float z_;
    std::shared_ptr<Material> material_;
};


#endif //RAY_TRACER_AARECT_H
