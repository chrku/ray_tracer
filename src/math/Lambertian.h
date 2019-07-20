//
// Created by christoph on 20.07.19.
//

#ifndef RAY_TRACER_LAMBERTIAN_H
#define RAY_TRACER_LAMBERTIAN_H

#include <random>

#include "Material.h"

class Lambertian : public Material {
public:
  explicit Lambertian(const Vec3& albedo, std::random_device& seed) : albedo_(albedo),
    prng_(seed()), dist_(0.f, 1.f) {}
  bool scatter(const Ray& ray_in, const HitRecord& record, Vec3& attenuation,
    Ray& ray_out) const override {
    Vec3 target = record.point + record.normal + generate_random_point_in_unit_sphere(dist_, prng_);
    ray_out = Ray(record.point, target - record.point);
    attenuation = albedo_;
    return true;
  }
private:
  Vec3 albedo_;
  mutable std::mt19937 prng_;
  mutable std::uniform_real_distribution<float> dist_;
};


#endif //RAY_TRACER_LAMBERTIAN_H