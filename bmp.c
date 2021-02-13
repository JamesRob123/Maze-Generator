#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

#define HEADER_SIZE 54

BITMAPHEADER bmp_create_bitmapheader(int height, int width) {
	BITMAPHEADER header = {};
	int padding = (4 - (width * 3) % 4) % 4;
	
	header.bfType = 0x4d42;
    header.bfSize = HEADER_SIZE + width * height * 3 + height * padding;
    header.bfReserved = 0;
    header.bfOffBits = HEADER_SIZE;
    header.biSize = 40;
    header.biWidth = width;
    header.biHeight = height;
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biCompression = 0;
    header.biSizeImage = width * height * 3 + height * padding;
    header.biXPelsPerMeter = 0;
    header.biYPelsPerMeter = 0;
    header.biClrUsed = 0;
    header.biClrImportant = 0;
	
	return header;
}

void bmp_create_image(BITMAPHEADER header, uint8_t *data, char *name) {
	int padding = (4 - (header.biWidth * 3) % 4) % 4;
	
	FILE *image = fopen(name, "w");
	unsigned char *buf = malloc(HEADER_SIZE + header.biHeight * header.biWidth * 3 + padding * header.biHeight);
	
	memcpy(buf, &header, HEADER_SIZE);
	memcpy(buf + HEADER_SIZE, data, header.biHeight * header.biWidth * 3 + padding * header.biHeight);

	fwrite(buf, 1, HEADER_SIZE + header.biHeight * header.biWidth * 3 + padding * header.biHeight, image);
	fclose(image);
	free(buf);
}