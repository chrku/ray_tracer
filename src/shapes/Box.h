//
// Created by christoph on 09.08.19.
//

#ifndef RAY_TRACER_BOX_H
#define RAY_TRACER_BOX_H

#include "Hitable.h"
#include "HitableCollection.h"

class Box : public Hitable {
public:
    template<typename MATERIAL_IMPL>
    Box(const Vec3 &p0, const Vec3 &p1, MATERIAL_IMPL &&material);

    bool hit(const Ray &r, float t0, float t1, HitRecord &record) const override;

    bool boundingBox(float t0, float t1, AABB &box) const override;

private:
    HitableCollection rects;
};


#endif //RAY_TRACER_BOX_H
