#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include "maze.h"
#include "helper.h"
#include "bmp.h"

void handle_invalid_usage(char *argv[]);
void handle_error(char *message);

/* 11584 on height and width was the largest numbers that worked for me on windows with the photos app */
int main(int argc, char *argv[]) {
	if (argc < 4) {
		handle_invalid_usage(argv);
	}
	
	size_t height = strtoull(argv[1], NULL, 10);
	size_t width = strtoull(argv[2], NULL, 10);
	char *filen_name = argv[3];
	
	/* Create the maze */
	maze_init();
	struct s_maze *maze = maze_create(height, width);
	if (maze == NULL) {
		handle_error("Error in maze_create()");
	}
	printf("Generating maze... ");
	int iResult = maze_generate(maze);
	if (iResult == -1) {
		printf("\n");
		handle_error("Error in maze_generate()");
	}
	printf("[done]\n");
	
	/* Convert maze to a raw maze */
	int new_height = (height * 2 + 1);
	int new_width = (width * 2 + 1);
	
	printf("Converting maze to other format... ");
	uint8_t *image_array = maze_to_image_array(maze);
	if (image_array == NULL) {
		printf("\n");
		handle_error("Error in maze_to_image_array()");
	}
	printf("[done]\n");
	maze_destroy(maze);

	/* Create image from image_array */
	printf("Creating image... ");
	BITMAPHEADER header = bmp_create_bitmapheader(new_height, new_width);
	bmp_create_image(header, image_array, filen_name);
	printf("[done]\n");
	
	free(image_array);
	return 0;
}

void handle_invalid_usage(char *argv[]) {
	fprintf(stderr, "Usage: %s <height> <width> <filename>\n", argv[0]);
	exit(EXIT_FAILURE);
}

void handle_error(char *message) {
	char *err_message = malloc(strlen(message) + 50);
	strcpy(err_message, message);
	strcat(err_message, " : terminating the process...");
	fprintf(stderr, "%s\n", message);
	free(err_message);
	exit(EXIT_FAILURE);
}