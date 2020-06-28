#include "raylib.h"
#include "drawfield.h"
#include "models.h"
#include "level_loader.h"
#include "level_state.h"
#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)

// Change this depending on the path of your executable relative to the assets folder
#define ASSET_PATH "assets/"
int grid_start_x = 0, grid_start_y = 0;
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
    load_models();

    //------- Level Setup
    empty_grid();
    load_level(0);
    place_obstacles_grid();

    Camera3D camera = (Camera3D){
        (Vector3){11.0f, 10.0f, -6.0f}, (Vector3){1.0f, 0.0f, -1.0f}, (Vector3){0.0f, 1.0f, 0.0f}, 45.0f, CAMERA_PERSPECTIVE};
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    GridLocation grid_loc;
    Direction active_dir = right;
    ModelId model_id = cable_straight;

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (IsKeyPressed('1'))
        {
            model_id = cable_straight;
        }
        else if (IsKeyPressed('2'))
        {
            model_id = net_switch;
        }
        else if (IsKeyPressed('3'))
        {
            model_id = cable_turn;
        }
        if (IsKeyPressed(KEY_R))
        {
            active_dir++;
            if (active_dir == 4)
            {
                active_dir = 0;
            }
        }
        grid_loc = get_cursor_indices(camera);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && get_grid_id(grid_loc.u, grid_loc.v) == -1)
        {
            place_obj(model_id, grid_loc.u, grid_loc.v, active_dir);
            deactivate_grid();
            grid_solver(grid_start_x, grid_start_y);
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(DARKGRAY);

        BeginMode3D(camera);

        draw_field(camera);

        EndMode3D();

        //------------UI------------

        DrawText(TextFormat("Selection: %i, %i, %i", model_id, grid_loc.u, grid_loc.v), 0, SCREEN_HEIGHT - 20, 20, GREEN);
        switch (active_dir)
        {
        case right:
            DrawText("right", 0, 0, 20, GREEN);
            break;
        case up:
            DrawText("up", 0, 0, 20, GREEN);
            break;
        case down:
            DrawText("down", 0, 0, 20, GREEN);
            break;
        case left:
            DrawText("left", 0, 0, 20, GREEN);
            break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    unload_models();
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context

    return 0;
}