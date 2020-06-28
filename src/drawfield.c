#include "drawfield.h"
#include "raylib.h"
#include <math.h>
#include "raymath.h"
#include "models.h"
#include "level_loader.h"
#include "level_state.h"
typedef enum GameState
{
    main_menu = 0,
    level = 1,
    end_screen = 2
} GameState;
extern GameState game_state;
GridLocation get_cursor_indices(Camera3D camera)
{
    Ray ray = GetMouseRay(GetMousePosition(), camera);
    RayHitInfo hit_info = GetCollisionRayGround(ray, 0.0f);
    GridLocation location;
    location.u = (BLOCK_SIZE * GRID_LENGTH / 2 - hit_info.position.x) / BLOCK_SIZE;
    location.v = (BLOCK_SIZE * GRID_LENGTH / 2 - hit_info.position.z) / BLOCK_SIZE;
    return location;
}
void draw_field(Camera3D camera)
{
    float x_offset = BLOCK_SIZE * GRID_LENGTH / 2 - BLOCK_SIZE / 2;
    float z_offset = BLOCK_SIZE * GRID_LENGTH / 2 - BLOCK_SIZE / 2;
    Color draw_color = WHITE;
    GridLocation location = get_cursor_indices(camera);

    //draw obstacles-------------------------------------------
    Model obstacle;
    for (int i = 0; i < get_obstacle_count(); i++)
    {
        obstacle = get_obstacle_id(obstacle_list[i].id);
        obstacle.transform = MatrixMultiply(MatrixRotateY(DEG2RAD * obstacle_list[i].dir * -90), obstacle.transform);
        DrawModel(obstacle, (Vector3){BLOCK_SIZE * GRID_LENGTH / 2 - BLOCK_SIZE / 2 - obstacle_list[i].x * BLOCK_SIZE, 0.0f, BLOCK_SIZE * GRID_LENGTH / 2 - BLOCK_SIZE / 2 - obstacle_list[i].y * BLOCK_SIZE}, 1.0f, WHITE);
    }

    for (int i = 0; i < GRID_LENGTH; i++)
    {
        x_offset = 0.0f + BLOCK_SIZE * GRID_LENGTH / 2 - BLOCK_SIZE / 2;
        for (int j = 0; j < GRID_LENGTH; j++)
        {
            if (get_grid_id(j, i) > -1)
            {
//draw interactives---------------------------------
#ifdef DEBUG_DRAW
                if (get_grid_active(j, i))
                {
                    if (get_grid_id(j, i) == laptop)
                        draw_color = GREEN;
                }
                else
#endif
                    draw_color = WHITE;
                DrawModel(get_grid_model(j, i), (Vector3){x_offset, 0.0f, z_offset}, 2.0f / 3, draw_color);
            }
            //draw grid---------------------
            if (j == location.u && i == location.v && game_state == level)
            {
                if (get_grid_id(j, i) == -1)
                {
                    DrawCube((Vector3){x_offset, -BLOCK_SIZE / 2, z_offset}, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, GREEN);
                }
                else
                {
                    DrawCube((Vector3){x_offset, -BLOCK_SIZE / 2, z_offset}, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, RED);
                }
            }
            else
            {
                DrawCube((Vector3){x_offset, -BLOCK_SIZE / 2, z_offset}, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, LIGHTGRAY);
            }
            DrawCubeWires((Vector3){x_offset, -BLOCK_SIZE / 2, z_offset}, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, GRAY);
            x_offset -= BLOCK_SIZE;
        }
        z_offset -= BLOCK_SIZE;
    }
}