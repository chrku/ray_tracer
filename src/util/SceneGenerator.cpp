//
// Created by christoph on 08.08.19.
//

#include "SceneGenerator.h"
#include "Texture.h"
#include "../math/Lambertian.h"
#include "../math/Sphere.h"
#include "../math/Metal.h"
#include "../math/Dielectric.h"

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

float SceneGenerator::getRandom() {
    std::uniform_real_distribution<float> dist(-1, 1);
    return dist(rng_);
}