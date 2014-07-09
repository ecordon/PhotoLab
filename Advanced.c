/*Advanced.c*/
/*Edwin Cordon*/

#include <stdio.h>
#include <assert.h>

#include "Advanced.h"

void age(IMAGE *image){

	unsigned int x, y;
	double b;

	assert(image);

	for(x = 0; x < image->Height; x++){
		for(y = 0; y < image->Width; y++){

			b = (double) (getRPixel(image, y, x) + getGPixel(image, y, x) + getBPixel(image, y, x))/5;

			setBPixel(image, y, x, (unsigned char) b);
			setRPixel(image, y, x, (unsigned char) b*1.6);
			setGPixel(image, y, x, (unsigned char) b*1.6);
		}
	}

	printf("Age operation done!\n");
}

void posterize(IMAGE *image, unsigned char rbits, unsigned char gbits, unsigned char bbits){

	unsigned int x, y;
	unsigned char rmask, gmask, bmask;

	assert(image);

	rmask = 1 << (rbits-1);
	gmask = 1 << (gbits-1);
	bmask = 1 << (bbits-1);	

	for(x = 0; x < image->Height; x++){
		for(y = 0; y < image->Width; y++){

			setRPixel(image, y, x, (~rmask & getRPixel(image, y, x)) | (rmask-1));
			setGPixel(image, y, x, (~gmask & getGPixel(image, y, x)) | (gmask-1));
			setBPixel(image, y, x, (~bmask & getBPixel(image, y, x)) | (bmask-1));
		}
	}

	printf("Posterize operation is done!\n");
}

IMAGE *blur(IMAGE *image){

	IMAGE *blurred;
	unsigned int i, j, x, y;
	unsigned int avg_r = 0, avg_g = 0, avg_b = 0;

	assert(image);

	blurred = createImage((image->Width), (image->Height));

	for(x = 1; x < image->Height-1; x++){
		for(y = 1; y < image->Width-1; y++){

			for(i = x-1; i <= x+1; i++){
				for(j = y-1; j <= y+1; j++){

					avg_r += getRPixel(image, j, i);
					avg_g += getGPixel(image, j, i);
					avg_b += getBPixel(image, j, i);
				}
			}

            setRPixel(blurred, y, x, (unsigned char)(avg_r/9));
			setGPixel(blurred, y, x, (unsigned char)(avg_g/9));
			setBPixel(blurred, y, x, (unsigned char)(avg_b/9));

            		// reset averages
            		avg_r = 0;
            		avg_g = 0;
            		avg_b = 0;
		}
	}
    
	deleteImage(image);
	printf("Blur operation is done!\n");

	return blurred;
}

void edge(IMAGE *image, double k){

	unsigned int x, y;
	double dr, dg, db, dy2, dx2;

	assert(image);

	for(x = 0; x < image->Height-1; x++){
		for(y = 0; y < image->Width-1; y++){

			// calculate d(image)/dy for r, g, b
			dr = (double) getRPixel(image, y, x) - getRPixel(image, y+1, x);
			dg = (double) getGPixel(image, y, x) - getGPixel(image, y+1, x);
			db = (double) getBPixel(image, y, x) - getBPixel(image, y+1, x);
			
			dy2 = dr*dr + dg*dg + db*db;

			// calculate d(image)/dx for r, g, b
			dr = (double) getRPixel(image, y, x) - getRPixel(image, y, x+1);
			dg = (double) getGPixel(image, y, x) - getGPixel(image, y, x+1);
			db = (double) getBPixel(image, y, x) - getBPixel(image, y, x+1);
			
			dx2 = dr*dr + dg*dg + db*db;
			
			// edge pixel if change in intensity is  greater than threshold
			if(k*k < dy2 || k*k < dx2)
			{
				setRPixel(image, y, x, 255); 
				setGPixel(image, y, x, 255); 
				setBPixel(image, y, x, 255); 
			}
			else
			{
				setRPixel(image, y, x, 0);
				setGPixel(image, y, x, 0);
				setBPixel(image, y, x, 0);
			}
		}
	}
	
	printf("Edge-detect operation is done!\n");
}

IMAGE *rotate(IMAGE *image){

	unsigned int x, y;
	unsigned char r, g, b;
	IMAGE *rimage;

	assert(image);

	rimage = createImage(image->Height, image->Width);	

	for(x = 0; x < image->Height; x++){
		for(y = 0; y < image->Width; y++){

			r = getRPixel(image, y, x);
			g = getGPixel(image, y, x);
			b = getBPixel(image, y, x);

			// algorithm organizes pixels for clockwise rotation
			setRPixel(rimage, (image->Height-1) - x, y, r);
			setGPixel(rimage, (image->Height-1) - x, y, g);
			setBPixel(rimage, (image->Height-1) - x, y, b);
		}
	}

    deleteImage(image);
	printf("Rotate operation is done!\n");

	return rimage;
}
