//
// Created by christoph on 17.07.19.
//

#include <vector>

#include "util/Color.h"
#include "file_formats/ImagePPM.h"

int main() {
  int width = 200;
  int height = 100;
  std::vector<ColorRGB> colorBuffer(width * height);
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      float r = static_cast<float>(i) / width;
      float g = static_cast<float>(j) / height;
      float b = 0.2;
      int ir = int(255.99 * r);
      int ig = int(255.99 * g);
      int ib = int(255.99 * b);
      colorBuffer[i + ((height - 1 - j) * width)].r = ir;
      colorBuffer[i + ((height - 1 - j) * width)].g = ig;
      colorBuffer[i + ((height - 1 - j) * width)].b = ib;
    }
  }

  write_image_ppm_ascii("/home/christoph/img.ppm", colorBuffer, width, height);

  return 0;
}