//
// Created by christoph on 20.07.19.
//

#ifndef RAY_TRACER_METAL_H
#define RAY_TRACER_METAL_H

#include <random>
#include <ctime>

#include "Material.h"

class Metal : public Material {
public:
  explicit Metal(const Vec3& albedo, float fuzz)
    : fuzziness_(std::min(fuzz, 1.f)), albedo_(albedo), dist_(0.f, 1.f) {
    auto time = static_cast<uint32_t>(std::time(nullptr));
    prng_ = std::mt19937(time);
  }
  bool scatter (const Ray& ray_in, const HitRecord& hit, Vec3& attenuation, Ray& ray_out) const override {
    Vec3 reflected = reflect(ray_in.direction(), hit.normal);
    ray_out = Ray(hit.point, reflected + (fuzziness_ * generate_random_point_in_unit_sphere(dist_, prng_)),
            ray_in.time());
    attenuation = albedo_;
    return (dot(ray_out.direction(), hit.normal) > 0);
  }
private:
  Vec3 albedo_;
  float fuzziness_;
  mutable std::mt19937 prng_;
  mutable std::uniform_real_distribution<float> dist_;
};


#endif //RAY_TRACER_METAL_H
