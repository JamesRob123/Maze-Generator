#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "array_list.h"			// Didn't wanna implement a stack so I used an array list
#include "maze.h"
#include "cell.h"

struct s_pos {
	int x;
	int y;
};

static struct s_pos __get_unvisited_neighbour(struct s_maze *maze, struct s_pos current_cell);
static void __shuffle_array(int *array, int size);
void __wall_remove(struct s_maze *maze, struct s_pos cell_1, struct s_pos cell_2);
void __create_start_end(struct s_maze *maze);

void maze_init() {
	srand(time(NULL));
}

struct s_maze *maze_create(int height, int width) {
	struct s_maze *maze = malloc(sizeof(struct s_maze));
	if (maze == NULL) {
		return NULL;
	}
	maze->height = height;
	maze->width = width;
	maze->cells = malloc(height * sizeof(struct s_cell *));
	if (maze->cells == NULL) {
		free(maze);
		return NULL;
	}
	for (int i = 0; i < height; ++i) {
		maze->cells[i] = malloc(width * sizeof(struct s_cell));
		if (maze->cells[i] == NULL) {
			/* Deallocates the rest of the maze if it could allocate new memory */
			for (int j = i - 1; j >= 0; --j) {
				free(maze->cells[j]);
			}
			free(maze->cells);
			free(maze);
			return NULL;
		}
		for (int j = 0; j < width; ++j) {
			cell_update(&(maze->cells[i][j]));
		}
	}
	return maze;
}

int maze_generate(struct s_maze *maze) {
	/* Using recursen */
	// struct s_pos pos = {0, 0};
	// int iResult = __maze_generate(maze, pos);
	
	/* Using iteration */
	struct array_list *st = array_list_create(sizeof(struct s_pos));
	struct s_pos current_cell = {0, 0};
	array_list_add(st, (void *)&current_cell);
	maze->cells[current_cell.y][current_cell.x].visited = true;
	
	while (st->length > 0) {
		/* Pop a cell from the stack */
		void *temp = array_list_get(st, st->length - 1);
		current_cell = *(struct s_pos *)temp;
		
		struct s_pos neighbour = __get_unvisited_neighbour(maze, current_cell);
		if (neighbour.x == -1 || neighbour.y == -1) {
			/* Didn't find a unvisited neighbour */
			array_list_remove(st, st->length - 1);
			continue;
		}
		__wall_remove(maze, current_cell, neighbour);
		maze->cells[neighbour.y][neighbour.x].visited = true;
		array_list_add(st, (void *)&neighbour);
	}
	__create_start_end(maze);
	array_list_free(st);
	return 1;
}

/*static int __maze_generate(struct s_maze *maze, struct s_pos current_cell) {
	maze->cells[current_cell.y][current_cell.x].visited = true;
	while (1) {
		struct s_pos neighbour = __get_unvisited_neighbour(maze, current_cell);
		if (neighbour.x == -1 || neighbour.y == -1) {
			return 1;
		}
		__wall_remove(maze, current_cell, neighbour);
		__maze_generate(maze, neighbour);
	}
	return 1;
}*/

static struct s_pos __get_unvisited_neighbour(struct s_maze *maze, struct s_pos current_cell) {
	int random_nums[4] = {0, 1, 2, 3};
	__shuffle_array(random_nums, 4);
	
	/* Selects one unvisited neighbour */
	struct s_pos neighbour = current_cell;
	for (short i = 0; i < 4; ++i) {
		switch (random_nums[i]) {
			case 0:
				/* Top neighbour */
				if (neighbour.y - 1 >= 0 && maze->cells[neighbour.y - 1][neighbour.x].visited == false) {
					neighbour.y -= 1;
					goto found_valid_neighbour;
				}
				break;
			case 1:
				/* Right neighbour */
				if (neighbour.x + 1 < maze->width && maze->cells[neighbour.y][neighbour.x + 1].visited == false) {
					neighbour.x += 1;
					goto found_valid_neighbour;
				}
				break;
			case 2:
				/* Down neighbour */
				if (neighbour.y + 1 < maze->height && maze->cells[neighbour.y + 1][neighbour.x].visited == false) {
					neighbour.y += 1;
					goto found_valid_neighbour;
				}
				break;
			case 3:
				/* Left neighbour */
				if (neighbour.x - 1 >= 0 && maze->cells[neighbour.y][neighbour.x - 1].visited == false) {
					neighbour.x -= 1;
					goto found_valid_neighbour;
				}
				break;
		}
	}
	/* Goes here if it didn't find any unvisited neighbour */
	struct s_pos pos = {-1, -1};
	return pos;
	
found_valid_neighbour:
	return neighbour;
}

static void __shuffle_array(int *array, int size) {
	for (short i = 0; i < size; ++i) {
		short j = rand() % size;
		int temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

void __wall_remove(struct s_maze *maze, struct s_pos cell_1, struct s_pos cell_2) {
	if (cell_1.y > cell_2.y) {
		maze->cells[cell_1.y][cell_1.x].wall_up = false;
		maze->cells[cell_2.y][cell_2.x].wall_down = false;
	} else if (cell_1.y < cell_2.y) {
		maze->cells[cell_1.y][cell_1.x].wall_down = false;
		maze->cells[cell_2.y][cell_2.x].wall_up = false;
	} else if (cell_1.x > cell_2.x) {
		maze->cells[cell_1.y][cell_1.x].wall_left = false;
		maze->cells[cell_2.y][cell_2.x].wall_right = false;
	} else if (cell_1.x < cell_2.x) {
		maze->cells[cell_1.y][cell_1.x].wall_right = false;
		maze->cells[cell_2.y][cell_2.x].wall_left = false;
	}
}

void __create_start_end(struct s_maze *maze) {
	int start = rand() % maze->width;
	int end = rand() % maze->width;
	maze->cells[0][start].wall_up = false;
	maze->cells[maze->height - 1][end].wall_down = false;
}

void maze_destroy(struct s_maze *maze) {
	for (int i = 0; i < maze->height; ++i) {
		free(maze->cells[i]);
	}
	free(maze->cells);
	free(maze);
}