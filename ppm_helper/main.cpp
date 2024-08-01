//
//  main.cpp
//  ppm_helper
//
//  Created by zhanwang-sky on 2024/8/1.
//

#include <cstdlib>
#include <iostream>
#include "ppm_helper.hpp"

using std::cout;
using std::cerr;
using std::endl;

unsigned char buf[8192 * 6144 * 3];

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "Usage: ./ppm_helper <input.ppm> <output.ppm>\n";
    exit(EXIT_FAILURE);
  }

  int w = -1, h = -1;
  int rc = 0;

  rc = ppm_read(argv[1], &w, &h, buf, sizeof(buf));
  if (rc != 0) {
    cerr << "fail to read ppm file, rc=" << rc << endl;
    exit(EXIT_FAILURE);
  }

  rc = ppm_write(argv[2], w, h, buf);
  if (rc != 0) {
    cerr << "fail to write ppm file, rc=" << rc << endl;
    exit(EXIT_FAILURE);
  }

  cout << "Done.\n";

  return 0;
}
