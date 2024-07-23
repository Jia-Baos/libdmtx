//
// Created by Jia-Baos on 2024/5/22.
//

#ifndef __IMAGE_IO_H__
#define __IMAGE_IO_H__

#include <stdlib.h>
#include "./image.h"

/* load a color image from a file in jpg or ppm*/
color_image *color_image_load(const char *fname);

/* write the color image to a ppn file */
void color_image_write(const char *fname, const color_image *img);

/* write the gray image to a ppn file */
void gray_image_write(const char *fname, const gray_image *img);

#endif  // !__IMAGE_IO_H__