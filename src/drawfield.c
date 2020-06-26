#include "drawfield.h"
#include "raylib.h"
#include <math.h>
#include "models.h"
typedef struct GridLocation
{
    int u;
    int v;
} GridLocation;
GridLocation get_cursor_indices(Camera3D camera)
{
    Ray ray = GetMouseRay(GetMousePosition(), camera);
    RayHitInfo hit_info = GetCollisionRayGround(ray, 0.0f);
    GridLocation location;
    location.u = (BLOCK_SIZE * GRID_LENGTH / 2 - hit_info.position.x) / BLOCK_SIZE;
    location.v = (BLOCK_SIZE * GRID_LENGTH / 2 - hit_info.position.z) / BLOCK_SIZE;
    //outside grid
    /*if (location.u < 0 || location.u >= GRID_LENGTH || location.v < 0 || location.v > GRID_LENGTH)
    {
        location.u = -1;
        location.v = -1;
    }*/
    return location;
}
void draw_field(Camera3D camera)
{
    float x_offset = BLOCK_SIZE * GRID_LENGTH / 2 - BLOCK_SIZE / 2;
    float z_offset = BLOCK_SIZE * GRID_LENGTH / 2 - BLOCK_SIZE / 2;
#define GRID_SELECTION
#ifdef GRID_SELECTION
    GridLocation location = get_cursor_indices(camera);
#endif
    for (int i = 0; i < GRID_LENGTH; i++)
    {
        x_offset = 0.0f + BLOCK_SIZE * GRID_LENGTH / 2 - BLOCK_SIZE / 2;
        for (int j = 0; j < GRID_LENGTH; j++)
        {
            //draw interactives
            DrawModel(get_grid(i, j), (Vector3){x_offset, BLOCK_SIZE / 2, z_offset}, .666666f, WHITE);
#ifdef GRID_SELECTION
            //draw grid
            if (j == location.u && i == location.v)
            {
                DrawCube((Vector3){x_offset, -BLOCK_SIZE / 2, z_offset}, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, GREEN);
                DrawCubeWires((Vector3){x_offset, -BLOCK_SIZE / 2, z_offset}, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, GRAY);
                x_offset -= BLOCK_SIZE;
                continue;
            }
#endif

            DrawCube((Vector3){x_offset, -BLOCK_SIZE / 2, z_offset}, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, LIGHTGRAY);
            DrawCubeWires((Vector3){x_offset, -BLOCK_SIZE / 2, z_offset}, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, GRAY);
            x_offset -= BLOCK_SIZE;
        }
        z_offset -= BLOCK_SIZE;
    }
}