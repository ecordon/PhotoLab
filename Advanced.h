/*Advanced.h*/
/*Edwin Cordon*/

#ifndef ADVANCED_H
#define ADVANCED_H

#include "Image.h"

void age(IMAGE *image);

void posterize(IMAGE *image, unsigned char rbits, unsigned char gbits, unsigned char bbits);

IMAGE *blur(IMAGE *image);

void edge(IMAGE *image, double k);

IMAGE *rotate(IMAGE *image);

#endif
