#include "raylib.h"


int main()
{
    
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Space Invaders");

    
    while (!WindowShouldClose())    
    {
        
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
       
    }

    
    CloseWindow();       
    
    return 0;
}