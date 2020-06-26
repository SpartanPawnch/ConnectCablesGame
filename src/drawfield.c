#include "drawfield.h"
#include "raylib.h"

void draw_field()
{
    float x_offset = 0.0f + BLOCK_SIZE * GRID_LENGTH / 2 - BLOCK_SIZE / 2;
    float z_offset = 0.0f - BLOCK_SIZE * GRID_LENGTH / 2 + BLOCK_SIZE / 2;
    for (int i = 0; i < GRID_LENGTH; i++)
    {
        x_offset = 0.0f + BLOCK_SIZE * GRID_LENGTH / 2 - BLOCK_SIZE / 2;
        for (int j = 0; j < GRID_LENGTH; j++)
        {
            DrawCube((Vector3){x_offset, -0.5f, z_offset}, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, LIGHTGRAY);
            DrawCubeWires((Vector3){x_offset, -0.5f, z_offset}, BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, GRAY);
            x_offset -= BLOCK_SIZE;
        }
        z_offset += BLOCK_SIZE;
    }
}