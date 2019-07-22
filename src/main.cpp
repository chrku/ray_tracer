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
#include "math/Lambertian.h"
#include "math/Metal.h"
#include "SimpleRecursiveRayTracer.h"
#include "math/HitableCollection.h"
#include "math/Dielectric.h"

int main() {
  int width = 400;
  int height = 200;
  ColorBuffer colorBuffer(width, height);
  SimpleRecursiveRayTracer ray_tracer(100);
  HitableCollection world;
  std::random_device seed_device;

  world.addHitable(Sphere(Vec3(1.f, 0.f, -1.f), 0.5, Metal(Vec3(0.8f, 0.6f, 0.2f), 1.f)));
  world.addHitable(Sphere(Vec3(-1.f, 0.f, -1.f), 0.5, Dielectric(1.5f)));
  world.addHitable(Sphere(Vec3(0.f,0.f,-1.f), 0.5f, Lambertian(Vec3(0.8f, 0.3f, 0.3f))));
  world.addHitable(Sphere(Vec3(0.f, -100.5, -1.f), 100.f, Lambertian(Vec3(0.8f, 0.8f, 0.f))));

  ray_tracer.render(world, colorBuffer);

  colorBuffer.writeAsPPM("/home/christoph/img.ppm");

  return 0;
}