//
// Created by christoph on 18.07.19.
//

#ifndef RAY_TRACER_UTIL_H
#define RAY_TRACER_UTIL_H

#include <random>

#include "Vec3.h"

float lerp(float a, float b, float t) {
  return (1 - t) * a + t * b;
}

Vec3 generate_random_point_unit_sphere(std::uniform_real_distribution<float>& distribution, std::mt19937& generator) {
  Vec3 p(0.f, 0.f, 0.f);
  do {
    p = 2 * Vec3(distribution(generator), distribution(generator), distribution(generator)) - Vec3(1.f, 1.f, 1.f);
  } while (dot(p, p) >= 1.0);
  return p;
}

#endif //RAY_TRACER_UTIL_H
