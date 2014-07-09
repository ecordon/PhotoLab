/* DIPs.c */
/* Edwin Cordon */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "DIPs.h"
#include "Image.h"

void blackNWhite(IMAGE *image){

	unsigned int x, y;
	unsigned char pixel;

	assert(image);

	for(x = 0; x < image->Height; x++){
		for(y = 0; y < image->Width; y++){

			pixel = (getRPixel(image, y, x) + getGPixel(image, y, x) + getBPixel(image, y, x))/3;
			
			setRPixel(image, y, x, pixel);
			setGPixel(image, y, x, pixel);
			setBPixel(image, y, x, pixel); 
		}
	}

	printf("Black and white operation is done!\n");
}

void negative(IMAGE *image){

	unsigned int x, y;

	assert(image);

	for(x = 0; x < image->Height; x++){
		for(y = 0; y < image->Width; y++){

			setRPixel(image, y, x, 255 - getRPixel(image, y, x));
			setGPixel(image, y, x, 255 - getGPixel(image, y, x));
			setBPixel(image, y, x, 255 - getBPixel(image, y, x)); 
		}
	}

	printf("Negative operation is done!\n");
}

void hFlip(IMAGE *image){

	unsigned int x, y;
	unsigned char r, g, b;

	assert(image);

	for(x = 0; x < image->Height; x++){
		for(y = 0; y < image->Width/2; y++){

			// buffer left-half of image
			r = getRPixel(image, y, x);
			g = getGPixel(image, y, x);
			b = getBPixel(image, y, x);

			// overwrite left-half pixels with right-half pixels
			setRPixel(image, y, x, getRPixel(image, (image->Width - 1) - y, x));
			setGPixel(image, y, x, getGPixel(image, (image->Width - 1) - y, x));
			setBPixel(image, y, x, getBPixel(image, (image->Width - 1) - y, x));
	
			// overwrite right-half pixels with buffer	
			setRPixel(image, (image->Width - 1) - y, x, r); 
			setGPixel(image, (image->Width - 1) - y, x, g); 
			setBPixel(image, (image->Width - 1) - y, x, b); 
		}
	}

	printf("Horizontal flip operation is done!\n");
}

void hMirror(IMAGE *image){

	unsigned int x, y;

	assert(image);

	for(x = 0; x < image->Height; x++){
		for(y = 0; y < image->Width/2; y++){

			setRPixel(image, (image->Width - 1) - y, x, getRPixel(image, y, x)); 
			setGPixel(image, (image->Width - 1) - y, x, getGPixel(image, y, x)); 
			setBPixel(image, (image->Width - 1) - y, x, getBPixel(image, y, x)); 
		}
	}

	printf("Horizontal mirror operation is done!\n");
}

void vFlip(IMAGE *image){

	unsigned int x, y;
	unsigned char r, g, b;

	assert(image);

	for(x = 0; x < image->Height/2; x++){
		for(y = 0; y < image->Width; y++){

			// buffer top-half of the image
			r = getRPixel(image, y, x);
			g = getGPixel(image, y, x);
			b = getBPixel(image, y, x);

			// overwrite top-half pixels with bottom-half pixels
			setRPixel(image, y, x, getRPixel(image, y, (image->Height - 1) - x));
			setGPixel(image, y, x, getGPixel(image, y, (image->Height - 1) - x));
			setBPixel(image, y, x, getBPixel(image, y, (image->Height - 1) - x));
		
			// overwrite bottom-half pixels with buffer
			setRPixel(image, y, (image->Height - 1) - x, r); 
			setGPixel(image, y, (image->Height - 1) - x, g); 
			setBPixel(image, y, (image->Height - 1) - x, b); 
		}
	}
	
	printf("Vertical filp operation is done!");
}

void vMirror(IMAGE *image){

	unsigned int x, y;

	assert(image);

	for(x = 0; x < image->Height/2; x++){
		for(y = 0; y < image->Width; y++){

			setRPixel(image, y, (image->Height - 1) - x, getRPixel(image, y, x)); 
			setGPixel(image, y, (image->Height - 1) - x, getGPixel(image, y, x)); 
			setBPixel(image, y, (image->Height - 1) - x, getBPixel(image, y, x)); 
		}
	}

	printf("Vertical Mirror operation is done!");
}

void border(IMAGE *image, unsigned int b_width, unsigned char r, unsigned char g, unsigned char b){

	unsigned int x, y;

	assert(image);

	for(x = 0; x < image->Height; x++){
		for(y = 0; y < image->Width; y++){

			if(x < b_width || x > image->Height - b_width)
			{
				setRPixel(image, y, x, r);
				setGPixel(image, y, x, g);
				setBPixel(image, y, x, b);
			}
			else
			{
				if(y < b_width || y > image->Width - b_width)
				{
					setRPixel(image, y, x, r);
					setGPixel(image, y, x, g);
					setBPixel(image, y, x, b);
				}
			}
		}
	}
	
	printf("Border operation is done!\n");	
}

void overlay(IMAGE *image, IMAGE *overlay, unsigned int y_offset, unsigned int x_offset){

	unsigned int x, y;
	unsigned char r, g, b;	

	assert(image);
	assert(overlay);

	/*overlay if overlaying image is within the original image*/
	if(y_offset < (image->Width - overlay->Width) && x_offset < (image->Height - overlay->Width)){

		for(x = 0; x < overlay->Height; x++){
			for(y = 0; y < overlay->Width; y++){

				r = getRPixel(overlay, y, x);
				g = getGPixel(overlay, y, x);
				b = getBPixel(overlay, y, x);
	
				// do not include white background from overlay image
				if(r < 250)
					setRPixel(image, y_offset + y, x_offset + x, r);
				if(g < 250)
					setGPixel(image, y_offset + y, x_offset + x, g);
				if(b < 250)
					setBPixel(image, y_offset + y, x_offset + x, b);
			}
		}
	}	
	else{
		printf("Unable to overlay image at (%d, %d)", x_offset, y_offset);
	}

	printf("Overlay operation is done!\n");
}

