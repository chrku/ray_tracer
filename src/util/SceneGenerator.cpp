//
// Created by christoph on 08.08.19.
//

#include "SceneGenerator.h"
#include "Texture.h"
#include "../materials/Lambertian.h"
#include "../shapes/Sphere.h"
#include "../materials/Metal.h"
#include "../materials/Dielectric.h"
#include "../materials/DiffuseLight.h"
#include "../shapes/AARect.h"
#include "../shapes/transformations/FlipNormals.h"

SceneGenerator::SceneGenerator() : rng_() {
}

void SceneGenerator::twoPerlinSpheres(HitableCollection &h) {
    std::shared_ptr<PerlinNoiseGenerator> generator = std::make_shared<PerlinNoiseGenerator>();
    std::shared_ptr<Texture> constant_1 = std::make_shared<ConstantTexture>(Vec3(0.9, 0.4, 0.3));
    std::shared_ptr<Texture> constant_2 = std::make_shared<ConstantTexture>(Vec3(0.3, 0.2, 0.3));
    std::shared_ptr<Texture> checker = std::make_shared<CheckerTexture>(constant_1, constant_2);
    std::shared_ptr<Texture> perlin = std::make_shared<PerlinNoiseTexture>(generator, 5.f);
    h.addHitable(Sphere(Vec3(0, -1000, 0), 1000, Lambertian(perlin)));
    h.addHitable(Sphere(Vec3(4, 1, 0), 1.f, Metal(Vec3(0.7, 0.6, 0.5), 0.f)));
    h.addHitable(Sphere(Vec3(0, 1, 0), 1.f, Dielectric(1.5)));
    h.addHitable(Sphere(Vec3(-4, 1, 0), 1.f, Lambertian(checker)));
}

void SceneGenerator::earthScene(HitableCollection &h) {
    std::shared_ptr<Texture> earth_texture = std::make_shared<ImageTexture>("../res/earth.jpg");
    h.addHitable(Sphere(Vec3(0,0,0), 5, Lambertian(earth_texture)));
}

float SceneGenerator::getRandom() {
    std::uniform_real_distribution<float> dist(-1, 1);
    return dist(rng_);
}

void SceneGenerator::simpleLight(HitableCollection &h) {
    std::shared_ptr<PerlinNoiseGenerator> generator = std::make_shared<PerlinNoiseGenerator>();
    std::shared_ptr<Texture> perlin = std::make_shared<PerlinNoiseTexture>(generator, 5.f);
    std::shared_ptr<Texture> light = std::make_shared<ConstantTexture>(Vec3(4.f, 4.f, 4.f));
    h.addHitable(Sphere(Vec3(0, -1000, 0), 1000, Lambertian(perlin)));
    h.addHitable(Sphere(Vec3(0, 2, 0), 2, Lambertian(perlin)));
    h.addHitable(Sphere(Vec3(0, 7, 0), 2, DiffuseLight(light)));
    h.addHitable(AARect(3, 5, 1, 3, -2, DiffuseLight(light)));
}

void SceneGenerator::cornellBox(HitableCollection &h) {
    std::shared_ptr<Texture> red = std::make_shared<ConstantTexture>(Vec3(0.65, 0.05, 0.05));
    std::shared_ptr<Texture> blue = std::make_shared<ConstantTexture>(Vec3(0.73, 0.73, 0.73));
    std::shared_ptr<Texture> green = std::make_shared<ConstantTexture>(Vec3(0.12, 0.45, 0.15));
    std::shared_ptr<Texture> white = std::make_shared<ConstantTexture>(Vec3(4.f, 4.f, 4.f));
    std::shared_ptr<Hitable> rect1 = std::make_shared<AARect>(0, 555, 0, 555, 555, Lambertian(green));
    h.addHitable(FlipNormals(rect1));
    h.addHitable(AARect(0, 555, 0, 555, 555, DiffuseLight(white)));
}
