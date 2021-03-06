#ifndef DRAWFIELD_H_GUARD
#define DRAWFIELD_H_GUARD
#define GRID_LENGTH 10
#define BLOCK_SIZE 1.0f
#include "raylib.h"
typedef struct GridLocation
{
    int u;
    int v;
} GridLocation;
GridLocation get_cursor_indices(Camera3D camera);
void draw_field(Camera3D camera);
#endif