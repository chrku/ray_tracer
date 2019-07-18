//
// Created by christoph on 18.07.19.
//

#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include "Vec3.h"
#include "Ray.h"
#include "Hitable.h"

class Sphere : public Hitable {
public:
  Sphere(const Vec3& center, float radius) : center_(center), radius_(radius) {}

  bool hit(const Ray& r, float t_min, float t_max, HitRecord& record) const override {
    Vec3 origin_center = r.origin() - center_;
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
        record.normal = (record.point - center_) / radius_;
        return true;
      }
      // Exit point
      float solution_2 = (-b + std::sqrt(discriminant)) / a;
      if (solution_2 < t_max && solution_2 > t_min) {
        record.t = solution_2;
        record.point = r.pointAtValue(record.t);
        record.normal = (record.point - center_) / radius_;
        return true;
      }
    }
    return false;
  }

  const Vec3& center() const { return center_; };
  float radius() const { return radius_; };
private:
  Vec3 center_;
  float radius_;
};


#endif //RAY_TRACER_SPHERE_H
