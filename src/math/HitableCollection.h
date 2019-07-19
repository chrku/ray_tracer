//
// Created by christoph on 20.07.19.
//

#ifndef RAY_TRACER_HITABLECOLLECTION_H
#define RAY_TRACER_HITABLECOLLECTION_H

#include <memory>
#include <vector>
#include <limits>

#include "Hitable.h"

class HitableCollection : public Hitable {
public:
  HitableCollection() = default;

  template<typename HITABLE_IMPL>
  void addHitable(HITABLE_IMPL&& hitable) {
    hitables.push_back(std::make_unique<HITABLE_IMPL>(hitable));
  }

  bool hit(const Ray& ray, float t_min, float t_max, HitRecord& record) const override {
    return Hitable::hitCollection(hitables.begin(), hitables.end(), ray,
      t_min , t_max, record);
  }

private:
  std::vector<std::unique_ptr<Hitable>> hitables;
};


#endif //RAY_TRACER_HITABLECOLLECTION_H
