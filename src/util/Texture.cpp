//
// Created by christoph on 04.08.19.
//

#include "Texture.h"

#include <utility>

ConstantTexture::ConstantTexture(const Vec3 &color) : color_(color) {}

Vec3 ConstantTexture::value(float u, float v, const Vec3 &point) const {
    return color_;
}

ConstantTexture::~ConstantTexture() = default;

CheckerTexture::CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd)
    : even_(std::move(even)), odd_(std::move(odd)) {}

Vec3 CheckerTexture::value(float u, float v, const Vec3 &point) const {
    float sine_value = std::sin(frequency_ * point.x()) *
            std::sin(frequency_ * point.y()) * std::sin(frequency_ * point.z());
    if (sine_value < 0)
        return odd_->value(u, v, point);
    else
        return even_->value(u, v, point);
}

CheckerTexture::~CheckerTexture() = default;

PerlinNoiseTexture::PerlinNoiseTexture(std::shared_ptr<PerlinNoiseGenerator> generator, float frequency)
    : generator_(std::move(generator)), frequency_(frequency)
{}

Vec3 PerlinNoiseTexture::value(float u, float v, const Vec3 &point) const {
    return Vec3(1, 1, 1) * 0.5f * (1 + generator_->noise(point * frequency_));
}

PerlinNoiseTexture::~PerlinNoiseTexture() = default;
