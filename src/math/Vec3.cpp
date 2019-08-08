//
// Created by christoph on 20.07.19.
//

#include "Vec3.h"

Vec3 generate_random_point_in_unit_sphere(std::uniform_real_distribution<float>& distribution, std::mt19937& generator) {
  Vec3 p(0.f, 0.f, 0.f);
  do {
    p = 2 * Vec3(distribution(generator), distribution(generator), distribution(generator)) - Vec3(1.f, 1.f, 1.f);
  } while (p.squaredNorm() >= 1.0);
  return p;
}

void getSphereUV(const Vec3& p, float& u, float& v) {
    float phi = std::atan2(p.z(), p.x());
    float theta = std::asin(p.y());
    u = 1.f - (phi + M_PI) / (2.f * M_PI);
    v = (theta + M_PI / 2.f) / M_PI;
}