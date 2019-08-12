//
// Created by christoph on 12.08.19.
//

#ifndef RAY_TRACER_TRANSLATE_H
#define RAY_TRACER_TRANSLATE_H


#include <memory>

#include "../../math/Vec3.h"
#include "../Hitable.h"

class Translate : public Hitable {
public:
    template<typename HITABLE_IMPL>
    Translate(HITABLE_IMPL hitable, const Vec3 &displacement)
            : containingObject_(std::make_shared<HITABLE_IMPL>(hitable)), offset_(displacement) {}

    bool hit(const Ray &r, float t_min, float t_max, HitRecord &record) const override {
        Ray moved(r.origin() - offset_, r.direction(), r.time());
        if (containingObject_->hit(moved, t_min, t_max, record)) {
            record.point += offset_;
            return true;
        }
        return false;
    }

    bool boundingBox(float t0, float t1, AABB &box) const override {
        if (containingObject_->boundingBox(t0, t1, box)) {
            box = AABB(box.min() + offset_, box.max() + offset_);
            return true;
        }
        return false;
    }

private:
    std::shared_ptr<Hitable> containingObject_;
    Vec3 offset_;
};


#endif //RAY_TRACER_TRANSLATE_H
