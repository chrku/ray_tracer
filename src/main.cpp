//
// Created by christoph on 17.07.19.
//

#include <vector>
#include <memory>
#include <limits>

#include "math/Vec3.h"
#include "math/Ray.h"
#include "file_formats/ImagePPM.h"
#include "util/ColorBuffer.h"
#include "math/Sphere.h"

Vec3 color(const Ray& ray, const std::vector<std::unique_ptr<Hitable>>& hitables) {
  HitRecord hitRecord{};
  float t = Hitable::hitCollection(hitables.begin(), hitables.end(), ray, 0.0, std::numeric_limits<float>::max(),
    hitRecord);
  if (t > 0.f) {
    Vec3 N = hitRecord.normal;
    return 0.5 * Vec3(N.x() + 1, N.y() + 1, N.z() + 1);
  }
  Vec3 unit_direction = normalize(ray.direction());
  t = 0.5 * (unit_direction.y() + 1.0);
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
  std::vector<std::unique_ptr<Hitable>> spheres;
  spheres.push_back(std::make_unique<Sphere>(Vec3(0,0,-1), 0.5));
  spheres.push_back(std::make_unique<Sphere>(Vec3(0,-100.5,-1), 100));
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