#include "raylib.h"
#include "Entitys/Player.h"
#include "Entitys/Enemy.h"

 int screenWidth = 800;
 int screenHeight = 600;

int main()
{

    InitWindow(screenWidth, screenHeight, "Space Invaders");

    Entity::Player player;
    Entity::Enemy enemy;
    Entity::initPlayer(player);
    Entity::initEnemy(enemy, screenWidth / 2, screenHeight * 0.1f);
    
    while (!WindowShouldClose())    
    {
        Entity::updatePlayer(player);
        Entity::updateEnemy(enemy);

        BeginDrawing();

        ClearBackground(BLACK);

        Entity::drawPlayer(player);
        Entity::drawEnemy(enemy);

        EndDrawing();
       
    }

    
    CloseWindow();       
    
    return 0;
}