//
// Created by christoph on 22.07.19.
//

#ifndef RAY_TRACER_DIELECTRIC_H
#define RAY_TRACER_DIELECTRIC_H

#include <ctime>
#include "Material.h"
#include "Vec3.h"

class Dielectric : public Material {
public:
  explicit Dielectric(float refractive_index) : refractiveIndex_(refractive_index), dist_(0.f, 1.f) {
    auto time = static_cast<uint32_t>(std::time(nullptr));
    prng_ = std::mt19937(time);
  }
  bool scatter(const Ray &ray_in, const HitRecord &hit, Vec3 &attenuation, Ray &ray_out) const override {
    Vec3 outward_normal{};
    Vec3 reflected = reflect(ray_in.direction(), hit.normal);
    float refraction_ratio;
    float cosine;
    attenuation = Vec3{1.f, 1.f, 1.f};
    // Calculate outward normal
    if (dot(ray_in.direction(), hit.normal) > 0.f) {
      outward_normal = -hit.normal;
      refraction_ratio = refractiveIndex_;
      cosine = refractiveIndex_ * dot(ray_in.direction(), hit.normal) / ray_in.direction().norm();
    }
    else {
      outward_normal = hit.normal;
      refraction_ratio = 1.f / refractiveIndex_;
      cosine = -dot(ray_in.direction(), hit.normal) / ray_in.direction().norm();
    }

    // Calculate reflection probability
    Vec3 refracted{};
    float reflection_probability;
    if (refract(ray_in.direction(), outward_normal, refraction_ratio, refracted)) {
      reflection_probability = schlick(cosine, refractiveIndex_);
    }
    // Reflect if no refraction possible
    else {
      reflection_probability = 1.f;
    }

    // Sample and check if value > probability
    if (dist_(prng_) < reflection_probability) {
      ray_out = Ray(hit.point, reflected);
    }
    else {
      ray_out = Ray(hit.point, refracted);
    }

    return true;
  }
private:
  bool refract(const Vec3& ray, const Vec3& normal, float refraction_constant, Vec3& refracted_dir) const {
    Vec3 normalized = normalize(ray);
    float dt = dot(normalized, normal);
    float discriminant = 1.f - refraction_constant * refraction_constant * (1 - dt * dt);
    if (discriminant > 0.f) {
      refracted_dir = refraction_constant * (normalized - normal * dt) - normal * std::sqrt(discriminant);
      return true;
    }
    else
      return false;
  }

  // Polynomial approximation by Christophe Schlick for refraction
  float schlick(float cosine, float refraction_index) const {
    float r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * std::pow((1 - cosine), 5);
  }

  float refractiveIndex_;

  mutable std::mt19937 prng_;
  mutable std::uniform_real_distribution<float> dist_;
};


#endif //RAY_TRACER_DIELECTRIC_H
