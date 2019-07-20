//
// Created by christoph on 20.07.19.
//

#ifndef RAY_TRACER_METAL_H
#define RAY_TRACER_METAL_H


#include "Material.h"
#include <random>

class Metal : public Material {
public:
  explicit Metal(const Vec3& albedo, float fuzz, std::random_device& device)
    : fuzziness_(std::min(fuzz, 1.f)), albedo_(albedo), prng_(device()), dist_(0.f, 1.f) {}
  bool scatter (const Ray& ray_in, const HitRecord& hit, Vec3& attenuation, Ray& ray_out) const override {
    Vec3 reflected = reflect(ray_in.direction(), hit.normal);
    ray_out = Ray(hit.point, reflected + (fuzziness_ * generate_random_point_in_unit_sphere(dist_, prng_)));
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
