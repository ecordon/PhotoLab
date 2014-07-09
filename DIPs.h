/*DIPs.h*/
/*Edwin Cordon*/

#ifndef DIPS_H
#define DIPS_H

#include "FileIO.h"

void blackNWhite(IMAGE *image);

void negative(IMAGE *image);

void hFlip(IMAGE *image);

void hMirror(IMAGE *image);

void vFlip(IMAGE *image);

void vMirror(IMAGE *image);

void border(IMAGE *image, unsigned int b_width, unsigned char R, unsigned char G, unsigned char B);

void overlay(IMAGE *image, IMAGE *overlay, unsigned int x_offset, unsigned int y_offset);

#endif
