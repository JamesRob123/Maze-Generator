#include <stdbool.h>
#include "cell.h"

struct s_cell cell_create() {
	struct s_cell cell;
	cell_update(&cell);
	return cell;
}

void cell_update(struct s_cell *cell) {
	cell->wall_up = true;
	cell->wall_right = true;
	cell->wall_down = true;
	cell->wall_left = true;
	cell->visited = false;
}