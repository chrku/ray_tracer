//
// Created by christoph on 18.07.19.
//

#include "ColorBuffer.h"
#include "../file_formats/ImagePPM.h"

ColorBuffer::ColorBuffer(std::size_t width, std::size_t height) : data_(width * height), width_(width), height_(height) {}

ColorBuffer::ColorBuffer(std::size_t width, std::size_t height, const Vec3 &value_default)
: data_(width * height, value_default),
  width_(width), height_(height)
{}

Vec3 &ColorBuffer::operator()(std::size_t index_y, std::size_t index_x) {
  return data_[index_x + (height_ - 1 - index_y) * width_];
}

bool ColorBuffer::writeAsPPM(const std::string &filename) {
  return write_image_ppm_ascii(filename, data_, width_, height_);
}

std::vector<Vec3> &ColorBuffer::data() {
  return data_;
}

Vec3 *ColorBuffer::dataPtr() {
  return data_.data();
}
