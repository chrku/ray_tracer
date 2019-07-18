//
// Created by christoph on 18.07.19.
//

#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include "Vec3.h"
#include "Ray.h"

class Sphere {
public:
  Sphere(const Vec3& center, float radius) : center_(center), radius_(radius) {}

  bool hasIntersection(const Ray& r) const {
      Vec3 origin_center = r.origin() - center_;
      // Solve quadratic
      float a = dot(r.direction(), r.direction());
      float b = 2.0 * dot(origin_center, r.direction());
      float c = dot(origin_center, origin_center) - radius_ * radius_;
      float discriminant = b * b - 4 * a * c;
      return discriminant > 0.f;
  }
private:
  Vec3 center_;
  float radius_;
};


#endif //RAY_TRACER_SPHERE_H
