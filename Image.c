/* Image.c */
/* Edwin Cordon */

#include <assert.h>
#include <stdlib.h>

#include "Image.h"

IMAGE *createImage(unsigned int Width, unsigned int Height){

	IMAGE *image;

	image = (IMAGE *)malloc(sizeof(IMAGE));

	image->Width = Width;
	image->Height = Height;

	/*Allocate memory for R, G and B pixels in image*/
	image->R = (unsigned char *)malloc(sizeof(unsigned char)*Width*Height);
	image->G = (unsigned char *)malloc(sizeof(unsigned char)*Width*Height);
	image->B = (unsigned char *)malloc(sizeof(unsigned char)*Width*Height);

	return image;
}

void deleteImage(IMAGE *image){

	assert(image);

	assert(image->R);
	free(image->R);

	assert(image->G);
	free(image->G);

	assert(image->B);
	free(image->B);	

	free(image);
}

unsigned char getRPixel(IMAGE *image, unsigned int y,  unsigned int x){

	assert(image);
	assert(y >= 0 && y < image->Width);
	assert(x >= 0 && x < image->Height);

	return *(image->R + y + x*(image->Width)); 
}

unsigned char getGPixel(IMAGE *image, unsigned int y,  unsigned int x){

	assert(image);
	assert(y >= 0 && y < image->Width);
	assert(x >= 0 && x < image->Height);
	
	return *(image->G + y + x*(image->Width)); 
}

unsigned char getBPixel(IMAGE *image, unsigned int y,  unsigned int x){

	assert(image);
	assert(y >= 0 && y < image->Width);
	assert(x >= 0 && x < image->Height);

	return *(image->B + y + x*(image->Width)); 
}

void setRPixel(IMAGE *image, unsigned int y,  unsigned int x, unsigned char r){

	assert(image);
	assert(y >= 0 && y < image->Width);
	assert(x >= 0 && x < image->Height);

	*((image->R) + y + x*(image->Width)) = r;
}

void setGPixel(IMAGE *image, unsigned int y,  unsigned int x, unsigned char g){

	assert(image);
	assert(y >= 0 && y < image->Width);
	assert(x >= 0 && x < image->Height);

	*((image->G) + y + x*(image->Width)) = g;
}

void setBPixel(IMAGE *image, unsigned int y,  unsigned int x, unsigned char b){

	assert(image);
	assert(y >= 0 && y < image->Width);
	assert(x >= 0 && x < image->Height);

	*((image->B) + y + x*(image->Width)) = b;
}

