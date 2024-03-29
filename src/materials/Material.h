//
// Created by christoph on 20.07.19.
//

#ifndef RAY_TRACER_MATERIAL_H
#define RAY_TRACER_MATERIAL_H


#include "../math/Ray.h"
#include "../shapes/Hitable.h"

class Material {
public:
  virtual bool scatter(const Ray& ray_in, const HitRecord& hit, Vec3& attenuation, Ray& ray_out) const = 0;
  virtual Vec3 emitted(float u, float v, const Vec3& p) const {
      return {0, 0, 0};
  }
  virtual ~Material() = default;
};


#endif //RAY_TRACER_MATERIAL_H
