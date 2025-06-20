#include "raylib.h"
#include "Entitys/Player.h"

 int screenWidth = 800;
 int screenHeight = 600;

int main()
{

    InitWindow(screenWidth, screenHeight, "Space Invaders");

    Entity::Player player;
    Entity::initPlayer(player);
    
    while (!WindowShouldClose())    
    {
        Entity::updatePlayer(player);

        BeginDrawing();

        ClearBackground(BLACK);

        Entity::drawPlayer(player);

        EndDrawing();
       
    }

    
    CloseWindow();       
    
    return 0;
}