//
// Created by christoph on 19.07.19.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include <random>

#include "Vec3.h"
#include "Ray.h"

class Camera {
public:
  explicit Camera(std::random_device& device) : origin_{0.f, 0.f, 0.f}, lowerLeftCorner_{-2.f, -1.f, -1.f},
    horizontal_{4.f, 0.f, 0.f}, vertical_{0.f, 2.f, 0.f}, prng_(device()),
    randomOffset_(0.f, 1.f) {}

  Ray getRay(float u, float v) { return {origin_, lowerLeftCorner_ + u * horizontal_ + v * vertical_ - origin_}; }
  Ray getRayRandomOffset(float u, float v, float width, float height) {
    u += randomOffset_(prng_) / width;
    v += randomOffset_(prng_) / height;
    return getRay(u, v);
  }

private:
  Vec3 origin_;
  Vec3 lowerLeftCorner_;
  Vec3 horizontal_;
  Vec3 vertical_;

  std::uniform_real_distribution<float> randomOffset_;
  std::mt19937 prng_;
};


#endif //RAY_TRACER_CAMERA_H
