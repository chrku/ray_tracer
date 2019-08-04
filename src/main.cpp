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
#include "math/BVH.h"

void generateRandomScene(HitableCollection &world) {
    std::shared_ptr<PerlinNoiseGenerator> generator = std::make_shared<PerlinNoiseGenerator>();
    std::shared_ptr<Texture> constant_1 = std::make_shared<ConstantTexture>(Vec3(0.9, 0.4, 0.3));
    std::shared_ptr<Texture> constant_2 = std::make_shared<ConstantTexture>(Vec3(0.3, 0.2, 0.3));
    std::shared_ptr<Texture> checker = std::make_shared<CheckerTexture>(constant_1, constant_2);
    std::shared_ptr<Texture> perlin = std::make_shared<PerlinNoiseTexture>(generator, 20.f);
    world.addHitable(Sphere(Vec3(0, -1000, 0), 1000, Lambertian(perlin)));
    world.addHitable(Sphere(Vec3(4, 1, 0), 1.f, Metal(Vec3(0.7, 0.6, 0.5), 0.f)));
    world.addHitable(Sphere(Vec3(0, 1, 0), 1.f, Dielectric(1.5)));
    world.addHitable(Sphere(Vec3(-4, 1, 0), 1.f, Lambertian(checker)));

}

int main() {
    int width = 400;
    int height = 200;
    float fovy = 20.f;
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

    generateRandomScene(world);
    BVH::BVHNode node(world, 0, world.length(), 0.f, 1.f);

    ray_tracer.render(node, colorBuffer);

    colorBuffer.writeAsPPM("/home/christoph/img.ppm");

    return 0;
}