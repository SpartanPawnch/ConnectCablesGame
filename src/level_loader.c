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
    case 1:
        //level info
        grid_start_x = 0;
        grid_start_y = 0;
        //add obstacles
        add_obstacle(speaker, 4, 5, right);
        add_obstacle(sofa, 3, 4, left);
        add_laptop(5, 5, right);
        break;
 case 9:
        //level info
        grid_start_x = 0;
        grid_start_y = 0;
        //add obstacles
        add_obstacle(sofa, 7, 3, right);
        add_obstacle(wall, 2, 0, right);
        add_obstacle(wall, 2, 2, right);
        add_obstacle(wall, 2, 3, right);
        add_obstacle(wall, 0, 5, right);
        add_obstacle(wall, 1, 5, right);
        add_obstacle(wall, 3, 6, up);
        add_obstacle(wall, 4, 6, up);
        add_obstacle(sofa, 3, 4, down);
        add_obstacle(speaker, 7, 5, right);
        add_obstacle(speaker, 5, 4, right);
        add_laptop(8, 5, down);
        break;
 case 10:
        //level info
        grid_start_x = 0;
        grid_start_y = 0;
        //add obstacles
        add_obstacle(speaker, 4, 5, right);
        add_laptop(5, 5, right);
        break;
 case 0:
        //level info
        grid_start_x = 0;
        grid_start_y = 6;
        //add obstacles
        add_obstacle(wall, 0, 5, up);
        add_obstacle(wall, 1, 5, up);
        add_obstacle(wall, 2, 5, up);
        add_obstacle(wall, 3, 5, up);
        add_obstacle(wall, 4, 5, up);
        add_obstacle(wall, 5, 5, up);
        add_obstacle(wardrobe, 6, 4, up);
        add_obstacle(speaker, 7, 2, right);
        add_obstacle(wardrobe, 5, 1, right);
        add_obstacle(wall, 0, 2, up);
        add_obstacle(wall, 1, 2, up);
        add_obstacle(wall, 2, 2, up);
        add_obstacle(wall, 3, 2, up);
        add_obstacle(sofa, 5, 7, up);
        add_laptop(0, 1, down);
        break;
 case 8:
        //level info
        grid_start_x = 0;
        grid_start_y = 7;
        //add obstacles
        add_obstacle(speaker, 3, 6, right);
        add_obstacle(speaker, 3, 4, right);
        add_obstacle(speaker, 5, 3, right);
        add_obstacle(wall, 9, 4, up);
        add_obstacle(wall, 8, 4, up);
        add_obstacle(wall, 7, 4, up);
        add_obstacle(wall, 5, 5, right);
        add_obstacle(wall, 5, 6, right);
        add_obstacle(wall, 7, 7, right);
        add_obstacle(wall, 7, 6, left);
        add_obstacle(sofa, 3, 8, left);
        add_obstacle(sofa, 8, 9, down);
        add_obstacle(wardrobe, 5, 9, left);
        add_obstacle(sofa, 3, 3, left);
        add_obstacle(wall, 6, 6, up);
        add_laptop(9, 7, up);
        add_laptop(6, 9, right);
        break;
 case 2:
        //level info
        grid_start_x = 4;
        grid_start_y = 0;
        //add obstacles
        add_obstacle(wall, 6, 0, right);
        add_obstacle(wall, 6, 1, right);
        add_obstacle(wall, 5, 1, right);
        add_obstacle(wall, 5, 2, right);
        add_obstacle(wall, 5, 3, right);
        add_obstacle(wall, 5, 4, up);
        add_obstacle(wall, 4, 4, up);
        add_obstacle(wall, 3, 4, up);
        add_obstacle(wall, 2, 4, up);
        add_obstacle(sofa, 1, 6, left);
        add_obstacle(wardrobe, 7, 3, right);
        add_obstacle(speaker, 9, 2, left);
        add_obstacle(speaker, 8, 5, left);
        add_laptop(9, 3, right);
        break;
 case 3:
        //level info
        grid_start_x = 0;
        grid_start_y = 9;
        //add obstacles
        add_obstacle(wall, 1, 9, right);
        add_obstacle(wall, 1, 8, right);
        add_obstacle(wall, 1, 7, right);
        add_obstacle(wall, 1, 6, right);
        add_obstacle(wall, 1, 5, right);
        add_obstacle(wall, 3, 4, right);
        add_obstacle(wall, 3, 5, right);
        add_obstacle(wall, 7, 0, right);
        add_obstacle(wall, 7, 1, right);
        add_obstacle(wall, 7, 2, right);
        add_obstacle(sofa, 3, 3, left);
        add_obstacle(sofa, 5, 5, down);
        add_obstacle(wardrobe, 9, 6, right);
        add_obstacle(wardrobe, 7, 6, left);
        add_obstacle(speaker, 4, 6, left);
        add_obstacle(speaker, 8, 4, left);
        add_laptop(9, 2, right);
        break;
 case 4:
        //level info
        grid_start_x = 7;
        grid_start_y = 0;
        //add obstacles
        for(int i=0;i<6;i++){add_obstacle(wall, 8, 0+i,right);}
        for(int i=0;i<5;i++){add_obstacle(wall, 2, 0+i,right);}
        add_obstacle(wall, 9, 7, up);
        add_obstacle(wall, 8, 7, up);
        add_obstacle(wall, 7, 7, up);
        add_obstacle(wall, 5, 7, up);
        add_obstacle(wall, 4, 7, up);
        add_obstacle(wall, 3, 7, up);
        add_obstacle(wall, 1, 7, up);
        add_obstacle(wall, 0, 7, up);
        add_obstacle(speaker, 7, 5, right);
        add_obstacle(speaker, 4, 8, right);
        add_obstacle(wardrobe, 7, 9, down);
        add_obstacle(sofa, 7, 3, right);
        add_obstacle(sofa, 3, 5, left);
        add_laptop(9, 8, up);
        add_laptop(3, 8, up);
        break;
 case 5:
        //level info
        grid_start_x = 9;
        grid_start_y = 0;
        //add obstacles
        add_obstacle(wall, 7, 0, right);
        add_obstacle(wall, 7, 1, right);
        add_obstacle(wall, 7, 2, right);
        add_obstacle(wall, 7, 3, right);
        add_obstacle(wall, 7, 5, right);
        add_obstacle(wall, 7, 6, right);
        add_obstacle(wall, 7, 7, right);
        add_obstacle(wall, 5, 1, right);
        add_obstacle(wall, 5, 2, right);
        add_obstacle(wall, 5, 6, right);
        add_obstacle(wall, 5, 7, right);
        add_obstacle(wall, 5, 8, right);
        add_obstacle(wall, 2, 7, right);
        add_obstacle(wall, 2, 8, right);
        add_obstacle(wall, 2, 9, right);
        add_obstacle(wall, 0, 7, right);
        add_obstacle(wall, 0, 6, right);
        add_obstacle(wall, 0, 5, right);
        add_obstacle(speaker, 3, 7, right);
        add_obstacle(speaker, 1, 5, right);
        add_obstacle(wardrobe, 4, 4, right);
        add_obstacle(sofa, 2, 1, left);
        add_obstacle(sofa, 2, 5, left);
        add_obstacle(sofa, 9, 4, right);
        add_obstacle(speaker, 2, 2, right);
        add_laptop(4, 9, right);
        add_laptop(0, 8, down);
        break;
 case 6:
        //level info
        grid_start_x = 9;
        grid_start_y = 8;
        //add obstacles
        add_obstacle(wall, 6, 9, right);
        add_obstacle(wall, 6, 8, right);
        add_obstacle(wall, 5, 8, up);
        add_obstacle(wall, 4, 8, up);
        add_obstacle(wall, 5, 6, up);
        add_obstacle(wall, 4, 6, up);
        add_obstacle(wall, 3, 6, up);
        add_obstacle(wall, 2, 6, up);
        add_obstacle(wall, 6, 0, right);
        add_obstacle(wall, 6, 1, right);
        add_obstacle(wall, 6, 2, right);
        add_obstacle(wall, 6, 3, right);
        add_obstacle(wall, 4, 1, up);
        add_obstacle(wall, 3, 1, up);
        add_obstacle(wall, 9, 5, up);
        add_obstacle(wall, 8, 5, up);
        add_obstacle(wall, 7, 5, up);
        add_obstacle(wardrobe, 5, 3, down);
        add_obstacle(wardrobe, 2, 7, right);
        add_obstacle(speaker, 3, 3, right);
        add_obstacle(speaker, 7, 3, right);
        add_obstacle(speaker, 0, 7, right);
        add_laptop(7, 0, right);
        add_laptop(5, 0, right);
        break;
 case 7:
        //level info
        grid_start_x = 0;
        grid_start_y = 6;
        //add obstacles
        add_obstacle(speaker, 2, 7, right);
        add_obstacle(speaker, 3, 5, right);
        add_obstacle(speaker, 5, 2, right);
        add_obstacle(wall, 9, 6, up);
        add_obstacle(wall, 8, 6, up);
        add_obstacle(wall, 7, 6, up);
        add_obstacle(wall, 6, 6, up);
        add_obstacle(wall, 5, 6, up);
        add_obstacle(wardrobe, 3, 7, right);
        add_obstacle(sofa, 6, 2, up);
        add_obstacle(sofa, 3, 2, up);
        add_laptop(8, 9, right);
        add_laptop(9, 3, up);
        add_laptop(4, 0, left);
        break;

    default:
        grid_start_x = 0;
        grid_start_y = 0;
        break;
    }
    place_obj(net_switch, grid_start_x, grid_start_y, right);
}