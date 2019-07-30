//
// Created by christoph on 19.07.19.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include <ctime>
#include <random>

#include "Vec3.h"
#include "Ray.h"

class Camera {
public:
  Camera(Vec3 look_from, Vec3 look_at, Vec3 world_up, float fovy, float aspect, float aperture,
    float focal_length, float t0, float t1) : origin_(look_from), lensRadius_(aperture / 2.f), dist_(0.f, 1.f),
    t0_(t0), t1_(t1) {
    float half_height = std::tan(fovy / 2.f);
    float half_width = aspect * half_height;
    w = normalize(look_from - look_at);
    u = normalize(cross(world_up, w));
    v = cross(w, u);
    lowerLeftCorner_ = origin_ - half_width * focal_length * u - half_height * focal_length * v -  focal_length * w;
    horizontal_ = 2 * half_width * focal_length * u;
    vertical_ = 2 * half_height * focal_length * v;

    // Initialize PRNG
    auto time = static_cast<uint32_t>(std::time(nullptr));
    prng_ = std::mt19937(time);
  }

  Ray getRay(float s, float t) {
    Vec3 random = lensRadius_ * generate_random_point_in_unit_sphere(dist_, prng_);
    Vec3 offset = u * random.x() + v * random.y();
    float time = dist_(prng_) * (t1_ - t0_);
    return {origin_ + offset, lowerLeftCorner_ + s * horizontal_ + t * vertical_ - origin_ - offset, time};
  }
private:
  Vec3 origin_;
  Vec3 lowerLeftCorner_{};
  Vec3 horizontal_{};
  Vec3 vertical_{};
  Vec3 u{}, w{}, v{};
  float lensRadius_ = 1.f;

  // Time values t0 = start, t1 = end
  float t0_;
  float t1_;

  std::mt19937 prng_;
  std::uniform_real_distribution<float> dist_;
};


#endif //RAY_TRACER_CAMERA_H
