#include "level_state.h"
#include "drawfield.h"
#include "models.h"
#include "raymath.h"
typedef struct GridObject
{
    ModelId type;
    Model model;
    Direction dir;
    bool active;
} GridObject;
static GridObject object_grid[GRID_LENGTH][GRID_LENGTH];
void populate_grid_rand()
{
    for (int i = 0; i < GRID_LENGTH; i++)
    {
        for (int j = 0; j < GRID_LENGTH; j++)
        {
            object_grid[i][j].type = GetRandomValue(0, NUM_MODELS - 1);
        }
    }
}
void empty_grid()
{
    for (int i = 0; i < GRID_LENGTH; i++)
    {
        for (int j = 0; j < GRID_LENGTH; j++)
        {
            object_grid[i][j].type = -1;
        }
    }
}
int get_grid_id(int x, int y)
{
    return object_grid[y][x].type;
}
void place_obj(ModelId id, int x, int y, Direction dir)
{
    object_grid[y][x].type = id;
    object_grid[y][x].model = get_model_id(id);
    object_grid[y][x].dir = dir;
    object_grid[y][x].active = false;
    object_grid[y][x].model.transform = MatrixMultiply(MatrixRotateY(DEG2RAD * object_grid[y][x].dir * 90), object_grid[y][x].model.transform);
}
bool get_grid_active(int x, int y)
{
    return object_grid[y][x].active;
}
void deactivate_grid()
{
    for (int i = 0; i < GRID_LENGTH; i++)
    {
        for (int j = 0; j < GRID_LENGTH; j++)
        {
            object_grid[i][j].active = false;
        }
    }
}
void grid_solver(int x, int y)
{
    object_grid[y][x].active = true;
    switch (object_grid[y][x].type)
    {
    case cable_straight:
    case cable_turn:
        switch (object_grid[y][x].dir)
        {
        case right:
            if (y + 1 < GRID_LENGTH && object_grid[y + 1][x].type != -1 && !object_grid[y + 1][x].active)
            {
                grid_solver(x, y + 1);
            }
            break;
        case up:
            if (x + 1 < GRID_LENGTH && object_grid[y][x + 1].type != -1 && !object_grid[y][x + 1].active)
                grid_solver(x + 1, y);
            break;
        case left:
            if (y - 1 >= 0 && object_grid[y - 1][x].type != -1 && !object_grid[y - 1][x].active)
                grid_solver(x, y - 1);
            break;
        case down:
            if (x - 1 >= 0 && object_grid[y][x - 1].type != -1 && !object_grid[y][x - 1].active)
                grid_solver(x - 1, y);
            break;
        }
        break;

    case net_switch:
        //right
        if (y + 1 < GRID_LENGTH && object_grid[y + 1][x].type != -1 && (object_grid[y + 1][x].type != cable_straight && object_grid[y + 1][x].type != cable_turn || object_grid[y + 1][x].dir == right) && !object_grid[y + 1][x].active)
        {
            grid_solver(x, y + 1);
        }
        if (x + 1 < GRID_LENGTH && object_grid[y][x + 1].type != -1 && (object_grid[y][x + 1].type != cable_straight && object_grid[y][x + 1].type != cable_turn || object_grid[y][x + 1].dir == up) && !object_grid[y][x + 1].active)
            grid_solver(x + 1, y);
        if (y - 1 >= 0 && object_grid[y - 1][x].type != -1 && (object_grid[y - 1][x].type != cable_straight && object_grid[y - 1][x].type != cable_turn || object_grid[y - 1][x].dir == left) && !object_grid[y - 1][x].active)
            grid_solver(x, y - 1);
        if (x - 1 >= 0 && object_grid[y][x - 1].type != -1 && (object_grid[y][x - 1].type != cable_straight && object_grid[y][x - 1].type != cable_turn || object_grid[y][x - 1].dir == down) && !object_grid[y][x - 1].active)
            grid_solver(x - 1, y);
        break;
    }
}
Model get_grid_model(int x, int y)
{
    return object_grid[y][x].model;
}