#ifndef LEVEL_STATE_H_GUARD
#define LEVEL_STATE_H_GUARD
#include "models.h"
typedef enum Direction
{
    right = 0,
    up = 1,
    left = 2,
    down = 3
} Direction;
int get_grid_id(int x, int y);
void populate_grid_rand();
void empty_grid();
void grid_solver(int x, int y);
bool get_grid_active(int x, int y);
void place_obj(ModelId id, int x, int y, Direction dir);
Model get_grid_model(int x, int y);
#endif