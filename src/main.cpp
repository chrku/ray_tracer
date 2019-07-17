//
// Created by christoph on 17.07.19.
//

#include <vector>

#include "math/Color.h"
#include "file_formats/ImagePPM.h"

int main() {
  int width = 200;
  int height = 100;
  std::vector<Vec3> colorBuffer(width * height);
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      Vec3 color(static_cast<float>(i) / width, static_cast<float>(j) / height, 0.5);
      colorBuffer[i + ((height - 1 - j) * width)] = color * 255.9;
    }
  }

  write_image_ppm_ascii("/home/christoph/img.ppm", colorBuffer, width, height);

  return 0;
}