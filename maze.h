#ifndef _MAZE_H_
#define _MAZE_H_

#include "cell.h"

struct s_maze {
	int height, width;
	struct s_cell **cells;
};

void maze_init();
struct s_maze *maze_create(int height, int width);
int maze_generate(struct s_maze *maze);
void maze_print(struct s_maze *maze);
void maze_destroy(struct s_maze *maze);

#endif