//
// Created by christoph on 18.07.19.
//

#include <fstream>

#include "ImagePPM.h"

bool write_image_ppm_ascii(const std::string& filename,
                           const std::vector<ColorRGB>& colors, std::size_t width,
                           std::size_t height) {
  // Check if width * height = size of color vector
  if (width * height != colors.size()) {
    std::cerr << "[ImagePPM] Dimensions do not match size of data" << std::endl;
    return false;
  }

  std::ofstream output_file_stream(filename);

  // Check for validity of stream
  if (!output_file_stream) {
    std::cerr << "[ImagePPM] Could not open file" << std::endl;
  }

  // Write header
  // ASCII
  output_file_stream << "P3" << std::endl;
  // Width and height
  output_file_stream << width << " " << height << std::endl;
  // RGB range
  output_file_stream << RGB_RANGE << std::endl;
  // Header done, write RGB triplets
  for (const auto& rgb : colors) {
    output_file_stream << static_cast<int>(rgb.r) << " "
                       << static_cast<int>(rgb.g) << " " << static_cast<int>(rgb.b) << std::endl;
  }

  std::cout << "[ImagePPM] Image successfully written" << std::endl;
  output_file_stream.close();

  return true;
}

bool write_image_ppm_ascii(const std::string& filename,
                           const std::vector<Vec3>& colors, std::size_t width,
                           std::size_t height) {
  // Check if width * height = size of color vector
  if (width * height != colors.size()) {
    std::cerr << "[ImagePPM] Dimensions do not match size of data" << std::endl;
    return false;
  }

  std::ofstream output_file_stream(filename);

  // Check for validity of stream
  if (!output_file_stream) {
    std::cerr << "[ImagePPM] Could not open file" << std::endl;
  }

  // Write header
  // ASCII
  output_file_stream << "P3" << std::endl;
  // Width and height
  output_file_stream << width << " " << height << std::endl;
  // RGB range
  output_file_stream << RGB_RANGE << std::endl;
  // Header done, write RGB triplets
  for (const auto& rgb : colors) {
    output_file_stream << static_cast<int>(rgb.r()) << " "
                       << static_cast<int>(rgb.g()) << " " << static_cast<int>(rgb.b()) << std::endl;
  }

  std::cout << "[ImagePPM] Image successfully written" << std::endl;
  output_file_stream.close();

  return true;
}

