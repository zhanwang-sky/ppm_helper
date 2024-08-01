//
//  ppm_helper.hpp
//  ppm_helper
//
//  Created by zhanwang-sky on 2024/8/1.
//

#ifndef ppm_helper_hpp
#define ppm_helper_hpp

int ppm_write(const char* filename, int width, int height,
              unsigned char* buf);

int ppm_read(const char* filename, int* width, int* height,
             unsigned char* buf, int bufsz);

#endif /* ppm_helper_hpp */
