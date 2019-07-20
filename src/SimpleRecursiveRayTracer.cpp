//
// Created by christoph on 20.07.19.
//

#include "SimpleRecursiveRayTracer.h"
#include "math/Material.h"

SimpleRecursiveRayTracer::SimpleRecursiveRayTracer() : device_(), prng_(device_()),
  dist_(0.f, 1.f), camera_(device_), numberOfSamples_(100) {}

SimpleRecursiveRayTracer::SimpleRecursiveRayTracer(int number_samples) : device_(), prng_(device_()),
  dist_(0.f, 1.f), camera_(device_), numberOfSamples_(number_samples) {}

void SimpleRecursiveRayTracer::render(const Hitable &object, ColorBuffer& framebuffer) {
  for (int j = 0; j < framebuffer.height(); ++j) {
    for (int i = 0; i < framebuffer.width(); ++i) {
      float u = static_cast<float>(i) / framebuffer.width();
      float v = static_cast<float>(j) / framebuffer.height();
      Vec3 color_average(0.f, 0.f, 0.f);
      for (int s = 0; s < numberOfSamples_; ++s) {
        Ray r = camera_.getRayRandomOffset(u, v, framebuffer.width(), framebuffer.height());
        color_average += color(r, object, 0);
      }
      framebuffer(j, i) = vec3_sqrt(color_average / numberOfSamples_) * 255.9;
    }
  }
}

Vec3 SimpleRecursiveRayTracer::color(const Ray& ray, const Hitable& object, int recursion_count) {
  HitRecord record{};
  // Check for object intersection
  bool hitsObject = object.hit(ray, 0.f, std::numeric_limits<float>::max(), record);
  if (hitsObject) {
    Ray scattered{};
    // Recursively trace reflection ray
    Vec3 attenuation(0.f, 0.f, 0.f);
    if (recursion_count < 50 && record.material->scatter(ray, record, attenuation, scattered)) {
      return attenuation * color(scattered, object, recursion_count + 1);
    }
    else {
      return {0.f, 0.f, 0.f};
    }
  }

  // Default background: Pseudo skybox
  Vec3 unit_direction = normalize(ray.direction());
  float t = 0.5 * (unit_direction.y() + 1.f);
  return lerp(Vec3(1.0, 1.0, 1.0), Vec3(0.5, 0.7, 1.0), t);
}
