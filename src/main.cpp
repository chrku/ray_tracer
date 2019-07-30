//
// Created by christoph on 17.07.19.
//

#include "math/Vec3.h"
#include "util/ColorBuffer.h"
#include "math/Sphere.h"
#include "math/MovingSphere.h"
#include "math/Camera.h"
#include "math/Lambertian.h"
#include "math/Metal.h"
#include "SimpleRecursiveRayTracer.h"
#include "math/HitableCollection.h"
#include "math/Dielectric.h"

void generateRandomScene(HitableCollection& world) {
  int n = 500;
  world.addHitable(Sphere(Vec3(0, -1000, 0), 1000, Lambertian(Vec3(0.5, 0.5, 0.5))));

  std::mt19937 prng;
  std::uniform_real_distribution<float> dist(0.f, 1.f);

  for (int a = -11; a < 11; ++a) {
    for (int b = -11; b < 11; ++b) {
      float choose_mat = dist(prng);
      Vec3 center(a + 0.9 * dist(prng), 0.2, b + 0.9 * dist(prng));
      if ((center - Vec3(4, 0.2, 0)).norm() > 0.9f) {
        if (choose_mat < 0.8) // diffuse
          world.addHitable(MovingSphere(center, center + Vec3(0.f, 0.5f * dist(prng), 0.f), 0.f, 1.f, 0.2, Lambertian(Vec3(dist(prng) * dist(prng), dist(prng) * dist(prng), dist(prng) * dist(prng)))));
        else if (choose_mat < 0.95) //metal
          world.addHitable(Sphere(center, 0.2, Metal(Vec3(dist(prng) * dist(prng), dist(prng) * dist(prng), dist(prng) * dist(prng)), 0.5 * dist(prng))));
        else
          world.addHitable(Sphere(center, 0.2, Dielectric(1.5)));
      }
    }
  }
  world.addHitable(Sphere(Vec3(0,1,0), 1.f, Dielectric(1.5)));
  world.addHitable(Sphere(Vec3(-4,1,0), 1.f, Lambertian(Vec3(0.4, 0.2, 0.1))));
  world.addHitable(Sphere(Vec3(4,1,0), 1.f, Metal(Vec3(0.7, 0.6, 0.5), 0.f)));
}

int main() {
  int width = 200;
  int height = 100;
  float fovy = 20.f;
  float a = static_cast<float>(width) / height;

  ColorBuffer colorBuffer(width, height);
  Camera camera(Vec3(13, 2, 3), Vec3(0,0,0), Vec3(0,1,0), fovy * M_PI / 180, a, 0.f, 10.f, 0.f, 1.f);
  SimpleRecursiveRayTracer ray_tracer(100, camera);
  HitableCollection world;

  generateRandomScene(world);

  ray_tracer.render(world, colorBuffer);

  colorBuffer.writeAsPPM("/home/christoph/img.ppm");

  return 0;
}