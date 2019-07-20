//
// Created by christoph on 19.07.19.
//

#ifndef RAY_TRACER_HITABLE_H
#define RAY_TRACER_HITABLE_H

#include <iterator>
#include <memory>

#include "Vec3.h"
#include "Ray.h"

class Material;

struct HitRecord {
  float t;
  Vec3 point;
  Vec3 normal;
  std::shared_ptr<Material> material;
};

class Hitable {
public:
  virtual bool hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const = 0;
  template<class Iterator>
  static bool hitCollection(Iterator begin, Iterator end, const Ray& r, float t_min, float t_max, HitRecord& record) {
    bool hit = false;
    float closest = t_max;

    // Check for every object if hit, update hit record if true
    while (begin != end) {
      const Hitable& h = **(begin)++;
      HitRecord temp{};
      if (h.hit(r, t_min, closest, temp)) {
        hit = true;
        closest = temp.t;
        record = temp;
      }
    }

    return hit;
  }
  virtual ~Hitable() = default;
};


#endif //RAY_TRACER_HITABLE_H
