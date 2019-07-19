//
// Created by christoph on 20.07.19.
//

#include "SimpleRecursiveRayTracer.h"

Vec3 generate_random_point_in_unit_sphere(std::uniform_real_distribution<float>& distribution, std::mt19937& generator) {
  Vec3 p(0.f, 0.f, 0.f);
  do {
    p = 2 * Vec3(distribution(generator), distribution(generator), distribution(generator)) - Vec3(1.f, 1.f, 1.f);
  } while (dot(p, p) >= 1.0);
  return p;
}

SimpleRecursiveRayTracer::SimpleRecursiveRayTracer() : device_(), prng_(device_()),
  dist_(0.f, 1.f), camera_(device_), numberOfSamples_(100) {}

void SimpleRecursiveRayTracer::render(const Hitable &object, ColorBuffer& framebuffer) {
  for (int j = 0; j < framebuffer.height(); ++j) {
    for (int i = 0; i < framebuffer.width(); ++i) {
      float u = static_cast<float>(i) / framebuffer.width();
      float v = static_cast<float>(j) / framebuffer.height();
      Vec3 color_average(0.f, 0.f, 0.f);
      for (int s = 0; s < numberOfSamples_; ++s) {
        Ray r = camera_.getRayRandomOffset(u, v, framebuffer.width(), framebuffer.height());
        color_average += color(r, object);
      }
      framebuffer(j, i) = vec3_sqrt(color_average / numberOfSamples_) * 255.9;
    }
  }
}

Vec3 SimpleRecursiveRayTracer::color(const Ray& ray, const Hitable& object) {
  HitRecord record{};
  // Check for object intersection
  bool hitsObject = object.hit(ray, 0.f, std::numeric_limits<float>::max(), record);
  if (hitsObject) {
    // Do lambertian reflection with absorption of 0.5
    Vec3 target = record.point + record.normal + generate_random_point_in_unit_sphere(dist_, prng_);
    // Recursively trace reflection ray
    return 0.5f * color(Ray(record.point, target - record.point), object);
  }

  // Default background: Pseudo skybox
  Vec3 unit_direction = normalize(ray.direction());
  float t = 0.5 * (unit_direction.y() + 1.f);
  return lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0), t);
}
