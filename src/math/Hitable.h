//
// Created by christoph on 19.07.19.
//

#ifndef RAY_TRACER_HITABLE_H
#define RAY_TRACER_HITABLE_H

#include <iterator>

#include "Vec3.h"
#include "Ray.h"

struct HitRecord {
  float t;
  Vec3 point;
  Vec3 normal;
};

class Hitable {
public:
  virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const = 0;
  template<class Iterator>
  static bool hitCollection(Iterator begin, Iterator end, const Ray& r, float t_min, float t_max, HitRecord& record) {
    bool hit = false;
    float closest = t_max;
    HitRecord temp{};

    // Check for every object if hit, update hit record if true
    while (begin != end) {
      const Hitable& h = **(begin)++;
      if (h.hit(r, t_min, closest, temp)) {
        hit = true;
        closest = record.t;
        record = temp;
      }
    }

    return hit;
  }
};


#endif //RAY_TRACER_HITABLE_H
