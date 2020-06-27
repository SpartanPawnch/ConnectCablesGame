#include "level_state.h"
#include "drawfield.h"
#include "models.h"
static int object_grid[GRID_LENGTH][GRID_LENGTH];
void populate_grid_rand()
{
    for (int i = 0; i < GRID_LENGTH; i++)
    {
        for (int j = 0; j < GRID_LENGTH; j++)
        {
            object_grid[i][j] = GetRandomValue(0, NUM_MODELS - 1);
        }
    }
}
void empty_grid()
{
    for (int i = 0; i < GRID_LENGTH; i++)
    {
        for (int j = 0; j < GRID_LENGTH; j++)
        {
            object_grid[i][j] = -1;
        }
    }
}
int get_grid_id(int x, int y)
{
    return object_grid[y][x];
}
void place_obj(ModelId id, int x, int y)
{
    object_grid[y][x] = id;
}