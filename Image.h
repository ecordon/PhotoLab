/* Image.h 
 * Original author: Weiwei Chen
 * Modified by: Edwin Cordon
 *
 * Comments: 
 *
 *      - (x,y) coordinate system follows convention used in image processing.
 *      - x defines vertical axis
 *      - y defines horizontal axis
 *
 * */

#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
	unsigned int Width;		/* image width */
	unsigned int Height; 	/* image height */
	unsigned char *R;		/* pointer to the memory storing all the R intensity values */
	unsigned char *G;		/* pointer to the memory storing all the G intensity values */
	unsigned char *B;		/* pointer to the memory storing all the B intensity values */
}IMAGE;

unsigned char getRPixel(IMAGE *image, unsigned int y,  unsigned int x);
unsigned char getGPixel(IMAGE *image, unsigned int y,  unsigned int x);
unsigned char getBPixel(IMAGE *image, unsigned int y,  unsigned int x);

void setRPixel(IMAGE *image, unsigned int y,  unsigned int x, unsigned char r);
void setGPixel(IMAGE *image, unsigned int y,  unsigned int x, unsigned char g);
void setBPixel(IMAGE *image, unsigned int y,  unsigned int x, unsigned char b);

IMAGE *createImage(unsigned int Width, unsigned int Height);
void deleteImage(IMAGE *image);

#endif
