#include "raylib.h"
#include "drawfield.h"
#include "models.h"
#include "level_loader.h"
#include "level_state.h"
#include <math.h>
#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)
typedef enum GameState
{
    main_menu = 0,
    level = 1,
    end_screen = 2
} GameState;
#define BOX_SPACING 20
#define OFFSET_LIMIT 5
GameState game_state = main_menu;
const int level_count = 2;
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

    //------- Camera Stuff

    Vector2 camera_offset = {0, 0};
    float camera_rot = 45.0f, default_camera_rot = 45.0f;
    Camera3D camera, default_camera = (Camera3D){
                         (Vector3){10.0f, 10.0f, 0.0f}, (Vector3){0.0f, 0.0f, 0.0f}, (Vector3){0.0f, 1.0f, 0.0f}, 45.0f, CAMERA_PERSPECTIVE};
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    camera = default_camera;
    GridLocation grid_loc;
    Direction active_dir = right;
    ModelId model_id = cable_straight;
    Rectangle level_icon_box = {90, 90, 150, 150};
    Vector2 icon_box_start = {90, 90};
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (game_state == main_menu)
        {
            level_icon_box.x = icon_box_start.x;
            level_icon_box.y = icon_box_start.y;
            for (int i = 0; i < level_count; i++)
            {
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), level_icon_box))
                {
                    empty_grid();
                    load_level(i);
                    place_obstacles_grid();
                    game_state = level;
                }
                level_icon_box.x += level_icon_box.width + BOX_SPACING;
            }
        }
        else if (game_state == level)
        {
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
#define CAMERA_MOVE_VELOCITY (0.2f);
            if (IsKeyDown(KEY_W))
            {
                //Caution - 2d to 3d coord conversions
                camera_offset.x += -sin(DEG2RAD * camera_rot) * CAMERA_MOVE_VELOCITY;
                camera_offset.y += cos(DEG2RAD * camera_rot) * CAMERA_MOVE_VELOCITY;
            }
            else if (IsKeyDown(KEY_S))
            {
                //Caution - 2d to 3d coord conversions
                camera_offset.x -= -sin(DEG2RAD * camera_rot) * CAMERA_MOVE_VELOCITY;
                camera_offset.y -= cos(DEG2RAD * camera_rot) * CAMERA_MOVE_VELOCITY;
            }
            if (IsKeyDown(KEY_D))
            {
                //Caution - 2d to 3d coord conversions
                camera_offset.x += cos(DEG2RAD * camera_rot) * CAMERA_MOVE_VELOCITY;
                camera_offset.y += sin(DEG2RAD * camera_rot) * CAMERA_MOVE_VELOCITY;
            }
            else if (IsKeyDown(KEY_A))
            {
                //Caution - 2d to 3d coord conversions
                camera_offset.x -= cos(DEG2RAD * camera_rot) * CAMERA_MOVE_VELOCITY;
                camera_offset.y -= sin(DEG2RAD * camera_rot) * CAMERA_MOVE_VELOCITY;
            }

            //limit camera movement
            if (camera_offset.x > OFFSET_LIMIT)
            {
                camera_offset.x = OFFSET_LIMIT;
            }
            if (camera_offset.x < -OFFSET_LIMIT)
            {
                camera_offset.x = -OFFSET_LIMIT;
            }
            if (camera_offset.y > OFFSET_LIMIT)
            {
                camera_offset.y = OFFSET_LIMIT;
            }
            if (camera_offset.y < -OFFSET_LIMIT)
            {
                camera_offset.y = -OFFSET_LIMIT;
            }
            if (IsKeyDown(KEY_E))
            {
#define ROTATE_VELOCITY 3.0f
                camera_rot += ROTATE_VELOCITY;
            }
            else if (IsKeyDown(KEY_Q))
            {
                camera_rot -= ROTATE_VELOCITY;
            }
            grid_loc = get_cursor_indices(camera);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && get_grid_id(grid_loc.u, grid_loc.v) == -1)
            {
                place_obj(model_id, grid_loc.u, grid_loc.v, active_dir);
                deactivate_grid();
                grid_solver(grid_start_x, grid_start_y);
            }
        }

        //normalise camera rotation

        while (camera_rot > 360)
        {
            camera_rot -= 360;
        }

        while (camera_rot < 0)
        {
            camera_rot += 360;
        }

        //rotate camera

        camera.position.x = default_camera.position.x * cos(DEG2RAD * camera_rot) - default_camera.position.z * sin(DEG2RAD * camera_rot);
        camera.position.z = default_camera.position.z * cos(DEG2RAD * camera_rot) - default_camera.position.x * sin(DEG2RAD * camera_rot);

        //translate camera

        camera.position.x -= camera_offset.y;
        camera.position.z -= camera_offset.x;
        camera.target.x = default_camera.target.x - camera_offset.y;
        camera.target.z = default_camera.target.z - camera_offset.x;

        //UpdateCamera(&camera);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(DARKGRAY);

        BeginMode3D(camera);

        draw_field(camera);

        EndMode3D();

        //------------UI------------

        if (game_state == main_menu)
        {
            level_icon_box.x = icon_box_start.x;
            level_icon_box.y = icon_box_start.y;
            for (int i = 0; i < level_count; i++)
            {
                DrawRectangleRec(level_icon_box, GRAY);
                DrawTextRec(GetFontDefault(), TextFormat(" %i", i), level_icon_box, 140, 0, false, GREEN);
                level_icon_box.x += level_icon_box.width + BOX_SPACING;
            }
        }
        else
        {
            DrawText(TextFormat("Selection: %i, %f, %f", model_id, camera_offset.x, camera_offset.y), 0, SCREEN_HEIGHT - 20, 20, GREEN);
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