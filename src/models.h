#ifndef MODELS_H_GUARD
#define MODELS_H_GUARD
#include "raylib.h"
#define NUM_MODELS 4
typedef enum ModelId
{
    cable_straight = 0,
    cable_turn = 1,
    net_switch = 2,
    laptop = 3
} ModelId;
void load_models();
Model *get_random_model_ptr();
Model get_model_id(int id);
void unload_models();
#endif