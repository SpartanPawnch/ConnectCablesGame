#include "raylib.h"
#include "drawfield.h"
#include "models.h"
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
    populate_grid_rand();
    Texture2D texture = LoadTexture(ASSET_PATH "test.png");

    Camera3D camera = (Camera3D){
        (Vector3){11.0f, 10.0f, -6.0f}, (Vector3){1.0f, 0.0f, -1.0f}, (Vector3){0.0f, 1.0f, 0.0f}, 45.0f, CAMERA_PERSPECTIVE};
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

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