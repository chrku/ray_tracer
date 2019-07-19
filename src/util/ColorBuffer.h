//
// Created by christoph on 18.07.19.
//

#ifndef RAY_TRACER_COLORBUFFER_H
#define RAY_TRACER_COLORBUFFER_H

#include <string>
#include <vector>

#include "../math/Vec3.h"

class ColorBuffer {
public:
  ColorBuffer(std::size_t width, std::size_t height);
  ColorBuffer(std::size_t width, std::size_t height, const Vec3& value_default);

  Vec3& operator()(std::size_t index_y, std::size_t index_x);

  bool writeAsPPM(const std::string& filename);

  std::vector<Vec3>& data();
  Vec3* dataPtr();

  inline std::size_t width() { return width_; }
  inline std::size_t height() { return height_; }
private:
  std::vector<Vec3> data_;

  std::size_t width_;
  std::size_t height_;
};


#endif //RAY_TRACER_COLORBUFFER_H
