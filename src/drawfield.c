#include "drawfield.h"
#include "raylib.h"
#include <math.h>
#include "models.h"
#include "level_state.h"

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
    GridLocation location = get_cursor_indices(camera);
    for (int i = 0; i < GRID_LENGTH; i++)
    {
        x_offset = 0.0f + BLOCK_SIZE * GRID_LENGTH / 2 - BLOCK_SIZE / 2;
        for (int j = 0; j < GRID_LENGTH; j++)
        {
            if (get_grid_id(j, i) != -1)
                //draw interactives
                DrawModel(get_model_id(get_grid_id(j, i)), (Vector3){x_offset, BLOCK_SIZE / 2, z_offset}, .666666f, WHITE);

            //draw grid
            if (j == location.u && i == location.v)
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