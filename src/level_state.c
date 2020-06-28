#include "level_state.h"
#include "drawfield.h"
#include "models.h"
#include "raymath.h"
#include "level_loader.h"
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
void place_obstacles_grid()
{
    for (int i = 0; i < get_obstacle_count(); i++)
    {
        if (obstacle_list[i].id == wall)
        {
            place_obj(obstacle_heavy, obstacle_list[i].x, obstacle_list[i].y, obstacle_list[i].dir);
        }
        else
        {
            for (int j = 0; j < obstacle_list[i].size_y; j++)
            {
                place_obj(obstacle_light, obstacle_list[i].x + j * (obstacle_list[i].dir % 2) * (1 - 2 * (obstacle_list[i].dir / 2)), obstacle_list[i].y + j * (1 - obstacle_list[i].dir % 2) * (1 - 2 * (obstacle_list[i].dir / 2)), obstacle_list[i].dir);
            }
        }
    }
}
/*
#define VALIDATE_RELATIVE(dir) (x - (dir % 2) * (1 - 2 * (dir / 2)) > 0 && x - (dir % 2) * (1 - 2 * (dir / 2)) < GRID_LENGTH && y - (1 - dir % 2) * (1 - 2 * (dir / 2)) > 0 && y - (1 - dir % 2) * (1 - 2 * (dir / 2)) < GRID_LENGTH)
#define TURNORSTRAIGHT(dirr) ((object_grid[y - (1 - dirr % 2) * (1 - 2 * (dirr / 2))][x - (dirr % 2) * (1 - 2 * (dirr / 2))].dir == dirr && object_grid[y - (1 - dirr % 2) * (1 - 2 * (dirr / 2))][x - (dirr % 2) * (1 - 2 * (dirr / 2))].type == cable_straight) || object_grid[y - (1 - dirr % 2) * (1 - 2 * (dirr / 2))][x - (dirr % 2) * (1 - 2 * (dirr / 2))].type == net_switch || (object_grid[y - (1 - dirr % 2) * (1 - 2 * (dirr / 2))][x - (dirr % 2) * (1 - 2 * (dirr / 2))].type == cable_turn && (object_grid[y - (1 - dirr % 2) * (1 - 2 * (dirr / 2))][x - (dirr % 2) * (1 - 2 * (dirr / 2))].dir + 1) % 4 == dirr || (object_grid[y - (1 - dirr % 2) * (1 - 2 * (dirr / 2))][x - (dirr % 2) * (1 - 2 * (dirr / 2))].dir + 2) % 4 == dirr))

ModelIdDir cable_select(int x, int y, Direction dir)
{
    ModelIdDir moddir = {0};
    if (VALIDATE_RELATIVE(dir) && TURNORSTRAIGHT(dir))
    {
        printf("straight\n");
        moddir.model_id = cable_straight;
        moddir.dir = dir;
        return moddir;
    }
    //clockwise
    if (VALIDATE_RELATIVE((dir + 1) % 4) && TURNORSTRAIGHT((dir + 1) % 4))
    {
        moddir.model_id = cable_turn;
        moddir.dir = dir;
        return moddir;
    }
    //anticlockwise
    if (VALIDATE_RELATIVE((dir + 3) % 4) && TURNORSTRAIGHT((dir + 3) % 4))
    {
        printf("cclock\n");
        moddir.model_id = cable_turn;
        moddir.dir = (dir + 3) % 4;
        return moddir;
    }
    //backwards
    if (VALIDATE_RELATIVE((dir + 2) % 4) && TURNORSTRAIGHT((dir + 2) % 4))
    {
        printf("back\n");
        moddir.model_id = cable_straight;
        moddir.dir = (dir + 2) % 4;
        return moddir;
    }
    moddir.model_id = cable_straight;
    moddir.dir = dir;
    return moddir;
}
*/
int get_grid_id(int x, int y)
{
    return object_grid[y][x].type;
}
void place_obj(ModelId id, int x, int y, Direction dir)
{
    object_grid[y][x].type = id;
    object_grid[y][x].dir = dir;
    object_grid[y][x].active = false;
    if (id >= 0)
    {
        object_grid[y][x].model = get_model_id(id);
        object_grid[y][x].model.transform = MatrixMultiply(MatrixRotateY(DEG2RAD * object_grid[y][x].dir * -90), object_grid[y][x].model.transform);
    }
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
    if (!object_grid[y][x].active)
    {
        object_grid[y][x].active = true;
        switch (object_grid[y][x].type)
        {
        case cable_straight:
            switch (object_grid[y][x].dir)
            {
            case right:
                if (y + 1 < GRID_LENGTH && object_grid[y + 1][x].type != -1)
                {
                    grid_solver(x, y + 1);
                }
                break;
            case up:
                if (x + 1 < GRID_LENGTH && object_grid[y][x + 1].type != -1)
                    grid_solver(x + 1, y);
                break;
            case left:
                if (y - 1 >= 0 && object_grid[y - 1][x].type != -1)
                    grid_solver(x, y - 1);
                break;
            case down:
                if (x - 1 >= 0 && object_grid[y][x - 1].type != -1)
                    grid_solver(x - 1, y);
                break;
            }
            break;
        case cable_turn:
            switch (object_grid[y][x].dir)
            {
            case right:
                if (y - 1 >= 0 && object_grid[y - 1][x].type != -1)
                    grid_solver(x, y - 1);
                if (x - 1 >= 0 && object_grid[y][x - 1].type != -1)
                    grid_solver(x - 1, y);
                break;
            case up:
                if (x - 1 >= 0 && object_grid[y][x - 1].type != -1)
                    grid_solver(x - 1, y);
                if (y + 1 < GRID_LENGTH && object_grid[y + 1][x].type != -1)
                    grid_solver(x, y + 1);
                break;
            case left:
                if (x + 1 < GRID_LENGTH && object_grid[y][x + 1].type != -1)
                    grid_solver(x + 1, y);
                if (y + 1 < GRID_LENGTH && object_grid[y + 1][x].type != -1)
                    grid_solver(x, y + 1);
                break;
            case down:
                if (x + 1 < GRID_LENGTH && object_grid[y][x + 1].type != -1)
                    grid_solver(x + 1, y);
                if (y - 1 >= 0 && object_grid[y - 1][x].type != -1)
                    grid_solver(x, y - 1);
                break;
            default:
                break;
            }
            break;
        case net_switch:
            //right
            if (y + 1 < GRID_LENGTH && object_grid[y + 1][x].type != -1 && (object_grid[y + 1][x].type != cable_straight && object_grid[y + 1][x].type != cable_turn || object_grid[y + 1][x].dir == right))
            {
                grid_solver(x, y + 1);
            }
            if (x + 1 < GRID_LENGTH && object_grid[y][x + 1].type != -1 && (object_grid[y][x + 1].type != cable_straight && object_grid[y][x + 1].type != cable_turn || object_grid[y][x + 1].dir == up))
                grid_solver(x + 1, y);
            if (y - 1 >= 0 && object_grid[y - 1][x].type != -1 && (object_grid[y - 1][x].type != cable_straight && object_grid[y - 1][x].type != cable_turn || object_grid[y - 1][x].dir == left))
                grid_solver(x, y - 1);
            if (x - 1 >= 0 && object_grid[y][x - 1].type != -1 && (object_grid[y][x - 1].type != cable_straight && object_grid[y][x - 1].type != cable_turn || object_grid[y][x - 1].dir == down))
                grid_solver(x - 1, y);
            break;
        }
    }
}
Model get_grid_model(int x, int y)
{
    return object_grid[y][x].model;
}