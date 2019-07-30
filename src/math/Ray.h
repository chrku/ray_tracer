//
// Created by christoph on 18.07.19.
//

#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H

#include "Vec3.h"

class Ray {
public:
  Ray() = default;
  Ray(const Vec3& origin, const Vec3& direction) : origin_(origin), direction_(direction), time_(0.f) {}
  Ray(const Vec3& origin, const Vec3& direction, float time) : origin_(origin), direction_(direction), time_(time) {}

  Vec3 origin() const { return origin_; };
  Vec3 direction() const { return direction_; }
  float time() const { return time_; }
  Vec3 pointAtValue(float t) const { return origin_ + (t * direction_); };
private:
  Vec3 origin_;
  Vec3 direction_;
  float time_;
};


#endif //RAY_TRACER_RAY_H
