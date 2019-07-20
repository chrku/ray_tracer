//
// Created by christoph on 20.07.19.
//

#ifndef RAY_TRACER_MATERIAL_H
#define RAY_TRACER_MATERIAL_H


#include "Ray.h"
#include "Hitable.h"

class Material {
public:
  virtual bool scatter(const Ray& ray_in, const HitRecord& hit, Vec3& attenuation, Ray& ray_out) const = 0;
  virtual ~Material() = default;
};


#endif //RAY_TRACER_MATERIAL_H
