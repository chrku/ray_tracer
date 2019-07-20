//
// Created by christoph on 20.07.19.
//

#include "Vec3.h"

Vec3 generate_random_point_in_unit_sphere(std::uniform_real_distribution<float>& distribution, std::mt19937& generator) {
  Vec3 p(0.f, 0.f, 0.f);
  do {
    p = 2 * Vec3(distribution(generator), distribution(generator), distribution(generator)) - Vec3(1.f, 1.f, 1.f);
  } while (dot(p, p) >= 1.0);
  return p;
}
