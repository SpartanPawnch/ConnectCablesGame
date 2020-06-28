extern int grid_start_x, grid_start_y;
#define MAX_LAPTOPS 20
#include "level_loader.h"
#include "drawfield.h"
ObstacleStandalone obstacle_list[MAX_OBSTACLES_ACTIVE];
GridLocation laptops[MAX_LAPTOPS];
int laptop_count = 0;
int obstacle_count = 0;
int get_obstacle_count()
{
    return obstacle_count;
}
ObstacleStandalone add_obstacle(ObstacleID id, int x, int y, Direction dir)
{
    ObstacleStandalone standalone;
    standalone.id = id;
    standalone.dir = dir;
    standalone.x = x;
    standalone.y = y;
    if (id == wardrobe || id == sofa)
    {
        standalone.size_y = 2;
    }
    else
    {
        standalone.size_y = 1;
    }
    if (obstacle_count < MAX_OBSTACLES_ACTIVE)
    {
        obstacle_list[obstacle_count] = standalone;
        obstacle_count++;
    }
}
void add_laptop(int x, int y, Direction dir)
{
    if (laptop_count < MAX_LAPTOPS)
    {
        laptops[laptop_count].u = x;
        laptops[laptop_count].v = y;
        laptop_count++;
        place_obj(laptop, x, y, dir);
    }
}
void load_level(int lv)
{
    obstacle_count = 0;
    switch (lv)
    {
    case 0:
        //level info
        grid_start_x = 0;
        grid_start_y = 0;
        //add obstacles
        add_obstacle(wall, 2, 0, right);
        add_laptop(5, 5, right);
        break;

    default:
        grid_start_x = 0;
        grid_start_y = 0;
        break;
    }
    place_obj(net_switch, grid_start_x, grid_start_y, right);
}