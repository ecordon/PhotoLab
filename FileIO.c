/* FileIO.c */
/* Edwin Cordon */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FileIO.h"

#define SLEN 100

IMAGE *readImage(const	char *fname){
	
	FILE *ppm;
	char extn_name[SLEN], TYPE[3];
	IMAGE *image;
	unsigned int width, height, x, y, intensity;

	strcpy(extn_name, fname);
	strcat(extn_name, ".ppm");

	if(!(ppm = fopen(extn_name, "r"))){
		fprintf(stderr, "ERROR: Could not open file for reading");
		return NULL;
	}

	// Check file format
	fscanf(ppm, "%79s", TYPE);
	if((strcmp(TYPE, "P6")) != 0){
		fprintf(stderr, "Unsupported file format\n");
		return NULL;
	}
	
	// Read width and height
	fscanf(ppm, "%d", &width); fscanf(ppm, "%d", &height);
	if(width < 0 || height < 0){
		fprintf(stderr, "Unsupported image width/height\n");
		return NULL;
	}

	// Read intensity range
	fscanf(ppm, "%d", &intensity);
	if(intensity != 255){
		fprintf(stderr, "Unsupported intensity range\n");
		return NULL;
	}
	
	if('\n' != fgetc(ppm)){
		fprintf(stderr, "Carriage return expected\n");
		return NULL;
	}

	image = createImage(width, height);		

	for(x = 0; x < image->Height; x++){
		for(y = 0; y < image->Width; y++){

			setRPixel(image, y, x, fgetc(ppm));
			setGPixel(image, y, x, fgetc(ppm));
			setBPixel(image, y, x, fgetc(ppm));
		}
	}

	printf("%s read successfully!\n", extn_name);

	fclose(ppm);
	return image;
}

int saveImage(const char *fname, IMAGE *image){

	FILE *ppm;
	char extn_name[SLEN];
	unsigned int x, y;

	strcpy(extn_name, fname);
	strcat(extn_name, ".ppm");

	if(!(ppm = fopen(extn_name, "w"))){
		perror("ERROR: Cannot open file for writing\n");
		return 1;
	}

	fprintf(ppm, "P6\n");
	fprintf(ppm, "%u %u\n", image->Width, image->Height);
	fprintf(ppm, "255\n");	

	for(x = 0; x < image->Height; x++){
		for(y = 0; y < image->Width; y++){
			
            fputc(getRPixel(image, y, x), ppm);
			fputc(getGPixel(image, y, x), ppm);
			fputc(getBPixel(image, y, x), ppm);
        }
	}

	printf("%s saved successfully!\n", extn_name);

	fclose(ppm);
	return 0;
}

