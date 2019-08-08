//
// Created by christoph on 17.07.19.
//

#include "math/Vec3.h"
#include "util/ColorBuffer.h"
#include "math/Sphere.h"
#include "math/Camera.h"
#include "SimpleRecursiveRayTracer.h"
#include "math/HitableCollection.h"
#include "math/BVH.h"
#include "util/SceneGenerator.h"

int main() {
    int width = 400;
    int height = 200;
    float fovy = 90.f;
    float a = static_cast<float>(width) / height;

    ColorBuffer colorBuffer(width, height);
    Camera camera(
            Vec3(13, 2, 3),
            Vec3(0, 0, 0),
            Vec3(0, 1, 0),
            fovy * M_PI / 180,
            a,
            0.f,
            10.f,
            0.f, 1.f);

    SimpleRecursiveRayTracer ray_tracer(100, camera);
    HitableCollection world;
    SceneGenerator generator;

    generator.earthScene(world);

    BVH::BVHNode node(world, 0, world.length(), 0.f, 1.f);

    ray_tracer.render(node, colorBuffer);

    colorBuffer.writeAsPPM("/home/christoph/img.ppm");

    return 0;
}