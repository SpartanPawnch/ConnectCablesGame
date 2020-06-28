#include "models.h"
#include "drawfield.h"
#include "raylib.h"

Model interactive_objects[NUM_MODELS];
Model obstacle_models[NUM_OBSTACLE_MODELS];
void load_models()
{

    interactive_objects[0] = LoadModel("assets/Plain_cable.obj");
    //Texture2D cable_texture=LoadTexture
    interactive_objects[1] = LoadModel("assets/Cable_turn.obj");
    interactive_objects[2] = LoadModel("assets/Switch.obj");
    interactive_objects[3] = LoadModel("assets/Laptop.obj");
    //interactive_objects[4] = LoadModel("assets/Router.obj");
    obstacle_models[0] = LoadModel("assets/Sofa.obj");
    obstacle_models[1] = LoadModel("assets/Wall.obj");
    obstacle_models[2] = LoadModel("assets/Wardrobe.obj");
    obstacle_models[3] = LoadModel("assets/Speaker.obj");
}
Model *get_random_model_ptr()
{
    return (interactive_objects + GetRandomValue(0, NUM_MODELS - 1));
}

Model get_model_id(int id)
{
    return interactive_objects[id];
}
Model get_obstacle_id(ObstacleID id)
{
    return obstacle_models[id];
}
void unload_models()
{
    for (int i = 0; i < NUM_MODELS; i++)
    {
        UnloadModel(interactive_objects[i]);
    }
    for (int i = 0; i < NUM_OBSTACLE_MODELS; i++)
    {
        UnloadModel(obstacle_models[i]);
    }
}