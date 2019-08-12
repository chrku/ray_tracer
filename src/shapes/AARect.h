//
// Created by christoph on 08.08.19.
//

#ifndef RAY_TRACER_AARECT_H
#define RAY_TRACER_AARECT_H


#include <utility>

#include "Hitable.h"

class XYRect : public Hitable {
public:
    template <typename MATERIAL_IMPL>
    XYRect(float x0, float x1, float y0, float y1, float z, MATERIAL_IMPL &&material)
        : x0_(x0), x1_(x1), y0_(y0), y1_(y1), z_(z), material_(std::make_shared<MATERIAL_IMPL>(material))
    {}

    XYRect(float x0, float x1, float y0, float y1, float z, std::shared_ptr<Material> material)
            : x0_(x0), x1_(x1), y0_(y0), y1_(y1), z_(z), material_(std::move(material)) {}

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
        box = AABB(Vec3(x0_, y0_, z_ - 0.01f), Vec3(x1_, y1_, z_ + 0.01f));
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

class YZRect : public Hitable {
public:
    template<typename MATERIAL_IMPL>
    YZRect(float y0, float y1, float z0, float z1, float x, MATERIAL_IMPL &&material)
            : y0_(y0), y1_(y1), z0_(z0), z1_(z1), x_(x), material_(std::make_shared<MATERIAL_IMPL>(material)) {}

    YZRect(float y0, float y1, float z0, float z1, float x, std::shared_ptr<Material> material)
            : y0_(y0), y1_(y1), z0_(z0), z1_(z1), x_(x), material_(std::move(material)) {}

    bool hit(const Ray &r, float t0, float t1, HitRecord &record) const override {
        float t = (x_ - r.origin().x()) / r.direction().x();
        if (t < t0 || t > t1)
            return false;
        float y = r.origin().y() + t * r.direction().y();
        float z = r.origin().z() + t * r.direction().z();
        if (y < y0_ || y > y1_ || z < z0_ || z > z1_)
            return false;

        record.u = (y - y0_) / (y1_ - y0_);
        record.v = (z - z0_) / (z1_ - z0_);
        record.t = t;
        record.material = material_;
        record.point = r.pointAtValue(t);
        record.normal = Vec3(1.f, 0.f, 0.f);
        return true;
    }

    bool boundingBox(float f0, float t1, AABB &box) const override {
        box = AABB(Vec3(x_ - 0.01f, y0_, z0_), Vec3(x_ + 0.01f, y1_, z1_));
        return true;
    }

private:
    float y0_;
    float y1_;
    float z0_;
    float z1_;
    float x_;
    std::shared_ptr<Material> material_;
};

class XZRect : public Hitable {
public:
    template<typename MATERIAL_IMPL>
    XZRect(float x0, float x1, float z0, float z1, float y, MATERIAL_IMPL &&material)
            : x0_(x0), x1_(x1), z0_(z0), z1_(z1), y_(y), material_(std::make_shared<MATERIAL_IMPL>(material)) {}

    XZRect(float x0, float x1, float z0, float z1, float y, std::shared_ptr<Material> material)
            : x0_(x0), x1_(x1), z0_(z0), z1_(z1), y_(y), material_(std::move(material)) {}

    bool hit(const Ray &r, float t0, float t1, HitRecord &record) const override {
        float t = (y_ - r.origin().y()) / r.direction().y();
        if (t < t0 || t > t1)
            return false;
        float x = r.origin().x() + t * r.direction().x();
        float z = r.origin().z() + t * r.direction().z();
        if (x < x0_ || x > x1_ || z < z0_ || z > z1_)
            return false;

        record.u = (x - x0_) / (x1_ - x0_);
        record.v = (z - z0_) / (z1_ - z0_);
        record.t = t;
        record.material = material_;
        record.point = r.pointAtValue(t);
        record.normal = Vec3(0.f, 1.f, 0.f);
        return true;
    }

    bool boundingBox(float f0, float t1, AABB &box) const override {
        box = AABB(Vec3(x0_, y_ - 0.01f, z0_), Vec3(x1_, y_ + 0.01f, z1_));
        return true;
    }

private:
    float x0_;
    float x1_;
    float z0_;
    float z1_;
    float y_;
    std::shared_ptr<Material> material_;
};

#endif //RAY_TRACER_AARECT_H
