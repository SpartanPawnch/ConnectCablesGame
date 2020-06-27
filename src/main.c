#include "raylib.h"
#include "drawfield.h"
#include "models.h"
#include "level_state.h"
#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)

// Change this depending on the path of your executable relative to the assets folder
#define ASSET_PATH "assets/"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window title");
    load_models();
    empty_grid();
    Texture2D texture = LoadTexture(ASSET_PATH "test.png");
    Camera3D camera = (Camera3D){
        (Vector3){11.0f, 10.0f, -6.0f}, (Vector3){1.0f, 0.0f, -1.0f}, (Vector3){0.0f, 1.0f, 0.0f}, 45.0f, CAMERA_PERSPECTIVE};
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    GridLocation grid_loc;
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        grid_loc = get_cursor_indices(camera);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && get_grid_id(grid_loc.u, grid_loc.v) == -1)
            place_obj(cable_straight, grid_loc.u, grid_loc.v);
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(DARKGRAY);

        BeginMode3D(camera);

        draw_field(camera);

        EndMode3D();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    unload_models();
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context

    return 0;
}