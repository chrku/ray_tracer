//
// Created by christoph on 04.08.19.
//

#include <algorithm>
#include <random>

#include "PerlinNoiseGenerator.h"

PerlinNoiseGenerator::PerlinNoiseGenerator() : xVals_(ARRAY_SIZE), yVals_(ARRAY_SIZE),
    zVals_(ARRAY_SIZE), randomValues_(ARRAY_SIZE) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        xVals_[i] = i;
        yVals_[i] = i;
        zVals_[i] = i;
    }

    std::mt19937 prng((std::random_device())());
    std::uniform_real_distribution<float> dist(-1.f, 1.f);

    std::shuffle(xVals_.begin(), xVals_.end(), prng);
    std::shuffle(yVals_.begin(), yVals_.end(), prng);
    std::shuffle(zVals_.begin(), zVals_.end(), prng);

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        randomValues_[i] = normalize(Vec3(dist(prng), dist(prng), dist(prng)));
    }
}

float PerlinNoiseGenerator::noise(const Vec3 &point) const {
    float u = point.x() - std::floor(point.x());
    float v = point.y() - std::floor(point.y());
    float w = point.z() - std::floor(point.z());
    int i = std::floor(point.x());
    int j = std::floor(point.y());
    int k = std::floor(point.z());

    std::array<Vec3, 8> corners{};

    for (int di = 0; di < 2; ++di) {
        for (int dj = 0; dj < 2; ++dj) {
            for (int dk = 0; dk < 2; ++dk) {
                Vec3 noise_corner = randomValues_[xVals_[(i + di) & 0xff] ^ yVals_[(j + dj) & 0xff] ^ zVals_[(k + dk) & 0xff]];
                corners[di * 4 + dj * 2 + dk] = noise_corner;
            }
        }
    }

    float color = trilinearInterpolation(corners, u, v, w);
    return color;
}

float PerlinNoiseGenerator::trilinearInterpolation(std::array<Vec3, 8> corners, float u, float v, float w) {
    float accumulator = 0.f;
    float uu = u*u*(3-2*u);
    float vv = v*v*(3-2*v);
    float ww = w*w*(3-2*w);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                Vec3 weight(u - i, v - j, w - k);
                accumulator += (i * uu + (1.f - i) * (1 - uu)) *
                               (j * vv + (1.f - j) * (1 - vv)) *
                               (k * ww + (1.f - k) * (1 - ww)) * dot(corners[i * 4 + j * 2 + k], weight);
            }
        }
    }

    return accumulator;
}

float PerlinNoiseGenerator::turbulence(Vec3 point, int octaves) const {
    float accumulator = 0.f;
    float weight = 1.0f;
    for (int i = 0; i < octaves; ++i) {
        accumulator += weight*noise(point);
        weight *= 0.5;
        point *= 2;
    }
    return std::abs(accumulator);
}
