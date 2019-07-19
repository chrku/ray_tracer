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
#include "math/Camera.h"
#include "math/Util.h"

Vec3 color(const Ray& ray, const std::vector<std::unique_ptr<Hitable>>& hitables,
  std::uniform_real_distribution<float>& distribution, std::mt19937& prng) {
  HitRecord hitRecord{};
  float t = Hitable::hitCollection(hitables.begin(), hitables.end(), ray, 0.0, std::numeric_limits<float>::max(),
    hitRecord);
  if (t > 0.f) {
    Vec3 target = hitRecord.point + hitRecord.normal + generate_random_point_unit_sphere(distribution, prng);
    return 0.5 * color(Ray(hitRecord.point, target - hitRecord.point), hitables,
      distribution, prng);
  }
  Vec3 unit_direction = normalize(ray.direction());
  t = 0.5 * (unit_direction.y() + 1.0);
  return lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0), t);
}

int main() {
  int width = 400;
  int height = 200;
  int number_samples = 100;
  ColorBuffer colorBuffer(width, height);

  std::random_device device;
  std::mt19937 prng(device());
  std::uniform_real_distribution<float> distribution(0.f, 1.f);

  Camera camera(device);

  std::vector<std::unique_ptr<Hitable>> spheres;
  spheres.push_back(std::make_unique<Sphere>(Vec3(0,0,-1), 0.5));
  spheres.push_back(std::make_unique<Sphere>(Vec3(0,-100.5,-1), 100));
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      float u = static_cast<float>(i) / width;
      float v = static_cast<float>(j) / height;
      Vec3 color_average(0.f, 0.f, 0.f);
      for (int s = 0; s < number_samples; ++s) {
        Ray r = camera.getRayRandomOffset(u, v, width, height);
        color_average += color(r, spheres, distribution, prng);
      }
      colorBuffer(j, i) = (color_average / number_samples) * 255.9;
    }
  }

  colorBuffer.writeAsPPM("/home/christoph/img.ppm");

  return 0;
}