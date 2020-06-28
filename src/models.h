#ifndef MODELS_H_GUARD
#define MODELS_H_GUARD
#include "raylib.h"
#define NUM_MODELS 4
#define NUM_OBSTACLE_MODELS 4
typedef enum ModelId
{
    obstacle_heavy = -3,
    obstacle_light = -2,
    empty = -1,
    cable_straight = 0,
    cable_turn = 1,
    net_switch = 2,
    laptop = 3
} ModelId;
typedef enum ObstacleID
{
    sofa = 0,
    wall = 1,
    wardrobe = 2,
    speaker = 3
} ObstacleID;
void load_models();
Model *get_random_model_ptr();
Model get_model_id(int id);
Model get_obstacle_id(ObstacleID id);
void unload_models();
#endif