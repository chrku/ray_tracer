//
// Created by christoph on 04.08.19.
//

#ifndef RAY_TRACER_PERLINNOISEGENERATOR_H
#define RAY_TRACER_PERLINNOISEGENERATOR_H

#include <array>

#include "Vec3.h"

class PerlinNoiseGenerator {
public:
    PerlinNoiseGenerator();
    float noise(const Vec3& point) const;
    float turbulence(Vec3 point, int octaves=7) const;
private:
    static float trilinearInterpolation(std::array<Vec3, 8> corners, float u, float v, float w);

    std::vector<std::uint32_t> xVals_;
    std::vector<std::uint32_t> yVals_;
    std::vector<std::uint32_t> zVals_;
    std::vector<Vec3> randomValues_;

    static constexpr int ARRAY_SIZE = 256;
};


#endif //RAY_TRACER_PERLINNOISEGENERATOR_H
