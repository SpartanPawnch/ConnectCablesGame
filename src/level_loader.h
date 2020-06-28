#ifndef LEVEL_LOAD_GUARD
#define LEVEL_LOAD_GUARD
#include "level_state.h"
#include "models.h"
extern int laptop_count;
extern int laptops_connected;
bool win_condition();
void load_level(int lv);
int get_obstacle_count();
typedef struct ObstacleStandalone
{
    ObstacleID id;
    Direction dir;
    int x;
    int y;
    int size_y;
} ObstacleStandalone;
#define MAX_OBSTACLES_ACTIVE 100
extern ObstacleStandalone obstacle_list[MAX_OBSTACLES_ACTIVE];
#endif