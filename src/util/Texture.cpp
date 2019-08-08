//
// Created by christoph on 04.08.19.
//

#include <utility>
#include <iostream>

#include "stb_image.h"
#include "Texture.h"


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
    return Vec3(1, 1, 1) * 0.5f * (1 + std::sin(frequency_ * point.z() + 10.f *  generator_->turbulence(point)));
}

PerlinNoiseTexture::~PerlinNoiseTexture() = default;

ImageTexture::ImageTexture(std::string image_path) {
    imageData_ = stbi_load(image_path.c_str(), &width_, &height_, &stride_, 0);
    if (imageData_) {
        std::cout << "[TEXTURE] Image loaded, width: " << width_ << " height: " << height_ << std::endl;
    }
    else {
        std::cout << "[TEXTURE] Failed to load image" << std::endl;
    }
}

ImageTexture::~ImageTexture() {
    if (imageData_ != nullptr)
        stbi_image_free(imageData_);
};

Vec3 ImageTexture::value(float u, float v, const Vec3 &point) const {
    int i = static_cast<int>(u * width_);
    int j = static_cast<int>((1 - v) * height_);
    if (i < 0) i = 0;
    if (j < 0) j = 0;
    if (i > width_ - 1) i = width_ - 1;
    if (j > height_ - 1) j = height_ - 1;
    float r = static_cast<int>(imageData_[3 * i + 3 * width_ * j]) / 255.f;
    float g = static_cast<int>(imageData_[3 * i + 3 * width_ * j + 1]) / 255.f;
    float b = static_cast<int>(imageData_[3 * i + 3 * width_ * j + 2]) / 255.f;
    return {r, g, b};
}

