/*PhotoLab.c*/
/*Edwin Cordon*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Image.h"
#include "DIPs.h"
#include "Advanced.h"

#define SLEN 80

void printUsage(void);

int main(int argc, const char *argv[]){

	unsigned int i = 1;
	IMAGE  *image;
	char fname[SLEN], sname[SLEN];

	if(argc < 3){
		printUsage();
	}
	
	sprintf(fname, "%s", argv[i]);
	if(!(image = readImage(fname))){

		fprintf(stderr, "Unable to read %s, terminating program!\n", fname);
		return -1;
	}
	i++;

	while(i < argc){
	
		if(argc-i >= 1){
		
			// convert image to black and white
			if((0 == strcmp(argv[i], "-bw"))){
				blackNWhite(image);
				i++;
			}

			// convert image to a negative
			else if((0 == strcmp(argv[i], "-neg"))){
				negative(image);
				i++;
			}

			// mirror image horizontally
			else if((0 == strcmp(argv[i], "-hm"))){
				hMirror(image);
				i++;
			}

			// flip image horizontally
			else if((0 == strcmp(argv[i], "-hf"))){
				hFlip(image);
				i++;
			}

			// mirror image vertically
			else if((0 == strcmp(argv[i], "-vm"))){
				vMirror(image);
				i++;
			}

			// flip image vertically
			else if((0 == strcmp(argv[i], "-vf"))){
				vFlip(image);
				i++;
			}

			// age image
			else if((0 == strcmp(argv[i], "-age"))){
				age(image);
				i++;
			}

			// blur image
			else if((0 == strcmp(argv[i], "-blr"))){
    			image = blur(image);
				i++;
			}

			// rotate image 90 degrees clockwise
			else if((0 == strcmp(argv[i], "-rot"))){
				image = rotate(image);
				i++;
			
			}
		}

		if(argc-i >= 2){

			// edge-detect image
			if((0 == strcmp(argv[i], "-edg"))){
				
				double threshold;
				i++;

				sscanf(argv[i], "%lf", &threshold);
				i++;

				edge(image, threshold);
			}

			// save image
			else if((0 == strcmp(argv[i], "-o"))){

				i++;
				sprintf(sname, "%s", argv[i]);
				i++;
			}
		}

		if(argc-i >= 5){

			// add border to image
			if((0 == strcmp(argv[i], "-bor"))){

				unsigned int bwidth, r, g, b;
				i++;

				sscanf(argv[i], "%u", &bwidth);
				i++;
				sscanf(argv[i], "%u", &r);
				i++;
				sscanf(argv[i], "%u", &g);
				i++;
				sscanf(argv[i], "%u", &b);
				i++;

				border(image, bwidth, r, g, b);
			}
		}

		if(argc-i >= 4){

			// add overlay to image
			if((0 == strcmp(argv[i], "-ovl"))){
				
				IMAGE *overlay_img;
				char fname2[SLEN];
				unsigned int x_offset, y_offset;
				i++;

				sprintf(fname2, "%s", argv[i]);
				if(!(overlay_img = readImage(fname2))){
					fprintf(stderr, "Unable to read %s, terminating program!\n", fname2);
					exit(1);
				}
				i++;
				
				sscanf(argv[i], "%u", &x_offset);
				i++;
				sscanf(argv[i], "%u", &y_offset);
				i++;
			
				overlay(image, overlay_img, y_offset, x_offset);
				deleteImage(overlay_img);
			}

			// posterize the image
			else if((0 == strcmp(argv[i], "-pos"))){
				
				unsigned char rbits, gbits, bbits;
				i++;

				sscanf(argv[i], "%hhu", &rbits);
				i++;
				sscanf(argv[i], "%hhu", &gbits);
				i++;
				sscanf(argv[i], "%hhu", &bbits);
				i++;

				posterize(image, rbits, gbits, bbits);
			}
		}
	}

	// save image
	if(!(0 == saveImage(sname, image))){
		fprintf(stderr, "Could not save file %s!\n", sname);
		return -2;
	}
	deleteImage(image);
	
	return 0;
}

void printUsage(void)
{
	printf("PhotoLab [input image] -[operation] [options] -o [output file name]\n");

	printf("Operations: \n");
	printf("-bw\tConvert image to black and white\n");
	printf("-neg\tTake the negative of an image\n");
	printf("-hf\tFlip image horizontally\n");
	printf("-hm\tMirror image horizontally\n");
	printf("-vf\tFlip image vertically\n");
	printf("-vm\tMirror image vertically\n");
	printf("-bor\tAdd border to image\n");
	printf("\t\tusage: -bor [width] [red] [green] [blue]\n");
	printf("-age\tAge image\n");
	printf("-pos\tPosterize image\n");
	printf("\t\tusage: -pos [red bits] [green bits] [blue bits]\n");
	printf("-blr\tBlur image\n");
	printf("-edg\tEdge-detect image\n");
	printf("\t\tusage: -edg [threshold]\n");
	printf("-rot\tRotate image clockwise by 90 degrees\n");
	printf("-ovl Overlay images\n");
	printf("\t\tusage: -ovl [overlay image]\n");
}
