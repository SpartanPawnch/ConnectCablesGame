#ifndef MODELS_H_GUARD
#define MODELS_H_GUARD
#include "raylib.h"
void load_models();
Model *get_random_model_ptr();
void populate_grid_rand();
Model get_grid(int x, int y);
void unload_models();
#endif