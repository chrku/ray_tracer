//
// Created by christoph on 04.08.19.
//

#ifndef RAY_TRACER_TEXTURE_H
#define RAY_TRACER_TEXTURE_H

#include <memory>

#include "../math/Vec3.h"
#include "../math/PerlinNoiseGenerator.h"

class Texture {
public:
    virtual Vec3 value(float u, float v, const Vec3& point) const = 0;
    virtual ~Texture() = default;
private:
};

class ConstantTexture : public Texture {
public:
    explicit ConstantTexture(const Vec3& color);
    ~ConstantTexture() override;
    Vec3 value(float u, float v, const Vec3& point) const override;
private:
    Vec3 color_{};
};

class CheckerTexture : public Texture {
public:
    CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);
    Vec3 value(float u, float v, const Vec3& point) const override;
    ~CheckerTexture() override;
private:
    std::shared_ptr<Texture> even_;
    std::shared_ptr<Texture> odd_;
    float frequency_ = 10.f;
};

class PerlinNoiseTexture : public Texture {
public:
    explicit PerlinNoiseTexture(std::shared_ptr<PerlinNoiseGenerator> generator, float frequency = 1.f);
    Vec3 value(float u, float v, const Vec3& point) const override ;
    ~PerlinNoiseTexture() override;
private:
    std::shared_ptr<PerlinNoiseGenerator> generator_;
    float frequency_;
};

#endif //RAY_TRACER_TEXTURE_H
