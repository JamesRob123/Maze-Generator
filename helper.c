#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "helper.h"

uint8_t *__maze_to_array(struct s_maze *maze);
static uint8_t **__maze_to_matrix(struct s_maze *maze);
static uint8_t *__matrix_to_array(uint8_t **matrix, int height, int width);
static uint8_t *__maze_array_to_image_array(uint8_t *maze_array, int height, int width);

uint8_t *maze_to_image_array(struct s_maze *maze) {
	uint8_t *maze_array = __maze_to_array(maze);
	if (maze_array == NULL) {
		return NULL;
	}
	uint8_t *image_array = __maze_array_to_image_array(maze_array, (maze->height * 2 + 1), (maze->width * 2 + 1));
	free(maze_array);
	return image_array;
}

uint8_t *__maze_to_array(struct s_maze *maze) {
	uint8_t **matrix = __maze_to_matrix(maze);
	if (matrix == NULL) {
		return NULL;
	}
	uint8_t *array = __matrix_to_array(matrix, maze->height * 2 + 1, maze->width * 2 + 1);
	for (int i = 0; i < maze->height * 2 + 1; ++i) {
		free(matrix[i]);
	}
	free(matrix);
	return array;
}

static uint8_t **__maze_to_matrix(struct s_maze *maze) {
	/* Need to allocate 2 times plus 1 more space because of the walls */
	uint8_t **matrix = malloc((maze->height * 2 + 1) * sizeof(uint8_t *));
	if (matrix == NULL) {
		return NULL;
	}
	for (int i = 0; i < maze->height * 2 + 1; ++i) {
		matrix[i] = malloc((maze->width * 2 + 1));
		if (matrix[i] == NULL) {
			for (int j = i - 1; j >= 0; --j) {
				free(matrix[j]);
			}
			free(matrix);
			return NULL;
		}
		memset(matrix[i], 1, (maze->width * 2 + 1));
	}
	for (int i = 0; i < maze->height; ++i) {
		for (int j = 0; j < maze->width; ++j) {
			int y = i * 2 + 1;
			int x = j * 2 + 1;
			matrix[y][x] = 0;
			if (maze->cells[i][j].wall_up == 0) {		
				matrix[y - 1][x] = 0;				
			}
			if (maze->cells[i][j].wall_down == 0) {
				matrix[y + 1][x] = 0;
			}
			if (maze->cells[i][j].wall_left == 0) {
				matrix[y][x - 1] = 0;
			}
			if (maze->cells[i][j].wall_right == 0) {
				matrix[y][x + 1] = 0;
			}
		}
	}
	return matrix;
}

static uint8_t *__matrix_to_array(uint8_t **matrix, int height, int width) {
	uint8_t *raw = malloc(height * (width + width % 4) * sizeof(uint8_t));
	if (raw == NULL) {
		return raw;
	}
	int n = 0;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			raw[n++] = matrix[i][j];
		}
	}
	return raw;
}

static uint8_t *__maze_array_to_image_array(uint8_t *maze_array, int height, int width) {
	/* Every line needs to be word(4 bytes) aligned and this is the padding if it isn't */
	int padding = (4 - (width * 3) % 4) % 4;
	uint8_t *image_array = malloc(height * width * 3 + padding * height);
	if (image_array == NULL) {
		return NULL;
	}
	for (int i = 0, j = 0; i < height * width; ++i) {
		/* Need to repeat 3 times because every pixel is 3 bytes*/
		for (int k = 0; k < 3; ++k) {
			image_array[j++] = maze_array[i] == 0 ? 0xff : 0;
		}
		if (i % width == width - 1) {
			for (int k = 0; k < padding; ++k) {
				image_array[j++] = 0;
			}
		}
	}
	return image_array;
}