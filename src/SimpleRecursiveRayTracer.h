//
// Created by christoph on 20.07.19.
//

#ifndef RAY_TRACER_SIMPLERECURSIVERAYTRACER_H
#define RAY_TRACER_SIMPLERECURSIVERAYTRACER_H

#include <random>

#include "util/ColorBuffer.h"
#include "math/Hitable.h"
#include "math/Camera.h"

class SimpleRecursiveRayTracer {
public:
  SimpleRecursiveRayTracer();
  explicit SimpleRecursiveRayTracer(int number_samples);
  SimpleRecursiveRayTracer(int number_samples, const Camera& camera);

  void render(const Hitable& object, ColorBuffer& framebuffer);
private:
  Vec3 color(const Ray& ray, const Hitable& object, int recursion_count);

  std::random_device device_;
  std::mt19937 prng_;
  std::uniform_real_distribution<float> dist_;

  Camera camera_;
  int numberOfSamples_;
};


#endif //RAY_TRACER_SIMPLERECURSIVERAYTRACER_H
