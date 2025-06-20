#include "raylib.h"
#include "Entitys/Player.h"
#include "Entitys/Enemy.h"
#include "Entitys/Bullet.h"
#include "vector"

 int screenWidth = 800;
 int screenHeight = 600;

 std::vector<Entity::Bullet> bullets;

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
        
        for (size_t i = 0; i < bullets.size(); i++)
        {
            Entity::updateBullet(bullets[i]);
        }

        BeginDrawing();

        ClearBackground(BLACK);

        Entity::drawPlayer(player);
        Entity::drawEnemy(enemy);

        for (size_t i = 0; i < bullets.size(); i++)
        {
            Entity::drawBullet(bullets[i]);
        }

        EndDrawing();
       
    }

    
    CloseWindow();       
    
    return 0;
}