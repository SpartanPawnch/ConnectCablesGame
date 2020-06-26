#include "models.h"
#include "drawfield.h"
#include "raylib.h"
#define NUM_MODELS 4
Model interactive_objects[NUM_MODELS];
int object_grid[GRID_LENGTH][GRID_LENGTH];
void load_models()
{
    interactive_objects[0] = LoadModel("assets/Plain_cable.obj");
    //interactive_objects[0].materials[0].maps[MAP_DIFFUSE].texture =
    interactive_objects[1] = LoadModel("assets/Cable_turn.obj");

    interactive_objects[2] = LoadModel("assets/Switch.obj");

    //interactive_objects[3] = LoadModel("assets/Router.obj");
    interactive_objects[3] = LoadModel("assets/Laptop.obj");
}
Model *get_random_model_ptr()
{
    return (interactive_objects + GetRandomValue(0, NUM_MODELS - 1));
}
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
Model get_grid(int x, int y)
{
    return (interactive_objects[object_grid[y][x]]);
}
void unload_models()
{
    for (int i = 0; i < NUM_MODELS; i++)
    {
        UnloadModel(interactive_objects[i]);
    }
}