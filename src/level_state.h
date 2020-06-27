#ifndef LEVEL_STATE_H_GUARD
#define LEVEL_STATE_H_GUARD
#include "models.h"
int get_grid_id(int x, int y);
void populate_grid_rand();
void empty_grid();
void place_obj(ModelId id, int x, int y);
#endif