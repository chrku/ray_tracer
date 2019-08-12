//
// Created by christoph on 09.08.19.
//

#ifndef RAY_TRACER_BOX_H
#define RAY_TRACER_BOX_H

#include "Hitable.h"
#include "HitableCollection.h"
#include "AARect.h"
#include "transformations/FlipNormals.h"

class Box : public Hitable {
public:
    template<typename MATERIAL_IMPL>
    Box(const Vec3 &p0, const Vec3 &p1, MATERIAL_IMPL &&material) : rects_(), pMin_(p0), pMax_(p1),
                                                                    material_(
                                                                            std::make_shared<MATERIAL_IMPL>(material)) {
        rects_.addHitable(XYRect(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), material_));
        rects_.addHitable(FlipNormals(XYRect(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), material_)));
        rects_.addHitable(XZRect(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), material_));
        rects_.addHitable(FlipNormals(XZRect(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), material_)));
        rects_.addHitable(YZRect(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), material_));
        rects_.addHitable(FlipNormals(YZRect(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), material_)));
    }

    bool hit(const Ray &r, float t0, float t1, HitRecord &record) const override {
        return rects_.hit(r, t0, t1, record);
    }

    bool boundingBox(float t0, float t1, AABB &box) const override {
        return rects_.boundingBox(t0, t1, box);
    }
private:
    HitableCollection rects_;
    Vec3 pMin_;
    Vec3 pMax_;
    std::shared_ptr<Material> material_;
};


#endif //RAY_TRACER_BOX_H
