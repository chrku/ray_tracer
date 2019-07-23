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
  explicit Camera() : origin_{0.f, 0.f, 0.f}, lowerLeftCorner_{-2.f, -1.f, -1.f},
    horizontal_{4.f, 0.f, 0.f}, vertical_{0.f, 2.f, 0.f} {}
  Camera(Vec3 look_from, Vec3 look_at, Vec3 world_up, float fovy, float aspect) : origin_(look_from) {
    float half_height = std::tan(fovy / 2.f);
    float half_width = aspect * half_height;
    Vec3 w = normalize(look_from - look_at);
    Vec3 u = normalize(cross(world_up, w));
    Vec3 v = cross(w, u);
    lowerLeftCorner_ = origin_ - half_width * u - half_height * v - w;
    horizontal_ = 2 * half_width * u;
    vertical_ = 2 * half_height * v;
  }

  Ray getRay(float u, float v) { return {origin_, lowerLeftCorner_ + u * horizontal_ + v * vertical_ - origin_}; }
private:
  Vec3 origin_;
  Vec3 lowerLeftCorner_{};
  Vec3 horizontal_{};
  Vec3 vertical_{};
};


#endif //RAY_TRACER_CAMERA_H
