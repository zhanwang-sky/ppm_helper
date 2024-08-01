//
//  ppm_helper.cpp
//  ppm_helper
//
//  Created by zhanwang-sky on 2024/8/1.
//

#include <climits>
#include <fstream>
#include <regex>
#include <string>
#include "ppm_helper.hpp"

int ppm_write(const char* filename, int width, int height,
              unsigned char* buf) {
  // sanity check
  if (!filename || width <= 0 || height <= 0 || !buf) {
    return INT_MIN;
  }

  std::ofstream ofs(filename, std::fstream::binary | std::fstream::trunc);
  if (!ofs) {
    return INT_MIN + 1;
  }

  ofs << "P6\n" << width << ' ' << height << "\n255\n";
  ofs.write(reinterpret_cast<char*>(buf), width * height * 3);
  if (!ofs) {
    return -1;
  }

  return 0;
}

int ppm_read(const char* filename, int* width, int* height,
             unsigned char* buf, int bufsz) {
  // sanity check
  if (!filename || !width || !height || !buf || bufsz <= 0) {
    return INT_MIN;
  }

  std::ifstream ifs(filename, std::fstream::binary);
  if (!ifs) {
    return INT_MIN + 1;
  }

  std::string line;
  std::smatch sm;
  std::regex e("^(\\d+) (\\d+)$");

  if (!std::getline(ifs, line) || line != "P6") {
    return -1;
  }

  if (!std::getline(ifs, line) || !std::regex_match(line, sm, e)) {
    return -2;
  }
  *width = std::stoi(sm[1]);
  *height = std::stoi(sm[2]);

  int realsz = (*width) * (*height) * 3;
  if (bufsz < realsz) {
    return realsz;
  }

  if (!std::getline(ifs, line) || line != "255") {
    return -3;
  }

  if (!ifs.read(reinterpret_cast<char*>(buf), realsz)) {
    return -4;
  }

  return 0;
}
