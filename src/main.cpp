//
// Created by christoph on 17.07.19.
//

#include <vector>

#include "math/Vec3.h"
#include "math/Ray.h"
#include "file_formats/ImagePPM.h"
#include "util/ColorBuffer.h"
#include "math/Sphere.h"

Vec3 color(const Ray& ray, const std::vector<Sphere>& spheres) {
  for (auto sphere: spheres) {
    if (sphere.hasIntersection(ray))
      return {1.f, 0.f, 0.f};
  }
  Vec3 unit_direction = normalize(ray.direction());
  float t = 0.5 * (unit_direction.y() + 1.0);
  return lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0), t);
}

int main() {
  int width = 200;
  int height = 100;
  ColorBuffer colorBuffer(width, height);
  Vec3 lower_left_corner(-2.0, -1.0, -1.0);
  Vec3 horizontal(4.0, 0.0, 0.0);
  Vec3 vertical(0.0, 2.0, 0.0);
  Vec3 origin(0.0, 0.0, 0.0);
  std::vector<Sphere> spheres;
  spheres.emplace_back(Vec3(0,0,-1), 0.5f);
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      float u = static_cast<float>(i) / width;
      float v = static_cast<float>(j) / height;
      Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
      colorBuffer(j, i) = color(r, spheres) * 255.9;
    }
  }

  colorBuffer.writeAsPPM("/home/christoph/img.ppm");

  return 0;
}