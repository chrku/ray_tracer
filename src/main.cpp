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
#include "SimpleRecursiveRayTracer.h"
#include "math/HitableCollection.h"

int main() {
  int width = 400;
  int height = 200;
  ColorBuffer colorBuffer(width, height);
  SimpleRecursiveRayTracer rayTracer;
  HitableCollection world;

  world.addHitable(Sphere(Vec3(0.f,0.f,-1.f), 0.5f));
  world.addHitable(Sphere(Vec3(0.f, -100.5, -1.f), 100.f));

  rayTracer.render(world, colorBuffer);

  colorBuffer.writeAsPPM("/home/christoph/img.ppm");

  return 0;
}