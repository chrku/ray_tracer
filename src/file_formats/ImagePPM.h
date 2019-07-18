//
// Created by christoph on 17.07.19.
//

#ifndef RAY_TRACER_IMAGEPPM_H
#define RAY_TRACER_IMAGEPPM_H

#include <string>
#include <vector>
#include <iostream>

#include "../math/Vec3.h"

constexpr int RGB_RANGE = 255;

bool write_image_ppm_ascii(const std::string& filename,
  const std::vector<Vec3>& colors, std::size_t width,
  std::size_t height);

#endif //RAY_TRACER_IMAGEPPM_H
