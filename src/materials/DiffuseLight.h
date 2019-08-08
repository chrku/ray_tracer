//
// Created by christoph on 08.08.19.
//

#ifndef RAY_TRACER_DIFFUSELIGHT_H
#define RAY_TRACER_DIFFUSELIGHT_H

#include "Material.h"
#include "../util/Texture.h"

class DiffuseLight : public Material {
public:
    DiffuseLight(std::shared_ptr<Texture> texture) : texture_(std::move(texture)) {}

    // This does not scatter rays
    bool scatter(const Ray& ray, const HitRecord& r, Vec3& attenuation, Ray& scattered) const override {
        return false;
    }
    Vec3 emitted(float u, float v, const Vec3& p) const override {
        return texture_->value(u, v, p);
    }

private:
    std::shared_ptr<Texture> texture_;
};


#endif //RAY_TRACER_DIFFUSELIGHT_H
