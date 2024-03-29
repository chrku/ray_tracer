//
// Created by christoph on 20.07.19.
//

#ifndef RAY_TRACER_LAMBERTIAN_H
#define RAY_TRACER_LAMBERTIAN_H

#include <random>
#include <ctime>
#include <utility>

#include "Material.h"
#include "../util/Texture.h"

class Lambertian : public Material {
public:
  explicit Lambertian(std::shared_ptr<Texture> texture_ptr) : texture_(std::move(texture_ptr)), dist_(0.f, 1.f) {
    auto time = static_cast<uint32_t>(std::time(nullptr));
    prng_ = std::mt19937(time);
  }
  bool scatter(const Ray& ray_in, const HitRecord& record, Vec3& attenuation,
    Ray& ray_out) const override {
    Vec3 target = record.point + record.normal + generate_random_point_in_unit_sphere(dist_, prng_);
    ray_out = Ray(record.point, target - record.point, ray_in.time());
    attenuation = texture_->value(record.u, record.v, record.point);
    return true;
  }
private:
  std::shared_ptr<Texture> texture_;
  mutable std::mt19937 prng_;
  mutable std::uniform_real_distribution<float> dist_;
};


#endif //RAY_TRACER_LAMBERTIAN_H
