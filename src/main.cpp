//
// Created by christoph on 17.07.19.
//

#include "math/Vec3.h"
#include "util/ColorBuffer.h"
#include "shapes/Sphere.h"
#include "math/Camera.h"
#include "SimpleRecursiveRayTracer.h"
#include "shapes/HitableCollection.h"
#include "math/BVH.h"
#include "util/SceneGenerator.h"

int main() {
    int width = 400;
    int height = 500;
    float fovy = 50.f;
    float a = static_cast<float>(width) / height;

    ColorBuffer colorBuffer(width, height);
    Camera camera(
            Vec3(278, 278, -800),
            Vec3(278, 278, 0),
            Vec3(0, 1, 0),
            fovy * M_PI / 180,
            a,
            0.f,
            10.f,
            0.f, 1.f);

    SimpleRecursiveRayTracer ray_tracer(300, camera);
    HitableCollection world;
    SceneGenerator generator;

    generator.cornellBoxFull(world);

    BVH::BVHNode node(world, 0, world.length(), 0.f, 1.f);

    ray_tracer.render(node, colorBuffer);

    colorBuffer.writeAsPPM("/home/christoph/img.ppm");

    return 0;
}