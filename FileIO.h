#ifndef FILE_IO_H
#define FILE_IO_H

#include "Image.h"

IMAGE *readImage(const	char *fname);
int saveImage(const char *fname, IMAGE *image);

#endif
