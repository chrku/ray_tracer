//
// Created by christoph on 09.08.19.
//

#ifndef RAY_TRACER_FLIPNORMALS_H
#define RAY_TRACER_FLIPNORMALS_H


#include "../Hitable.h"

class FlipNormals : public Hitable {
public:
    explicit FlipNormals(std::shared_ptr<Hitable> hitable) : containingObject_(std::move(hitable)) {}

    template<typename HITABLE_IMPL>
    FlipNormals(HITABLE_IMPL h) : containingObject_(std::make_shared<HITABLE_IMPL>(h)) {}

    bool hit(const Ray &ray, float t_min, float t_max, HitRecord &record) const override {
        if (containingObject_->hit(ray, t_min, t_max, record)) {
            record.normal = -record.normal;
            return true;
        } else
            return false;
    }

    bool boundingBox(float t0, float t1, AABB &box) const override {
        return containingObject_->boundingBox(t0, t1, box);
    }

private:
    std::shared_ptr<Hitable> containingObject_;
};


#endif //RAY_TRACER_FLIPNORMALS_H
