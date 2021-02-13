#ifndef _CELL_H_
#define _CELL_H_

#include <stdbool.h>

struct s_cell {
	bool wall_up;
	bool wall_right;
	bool wall_down;
	bool wall_left;
	bool visited;
};

struct s_cell cell_create();
void cell_update(struct s_cell *cell);

#endif