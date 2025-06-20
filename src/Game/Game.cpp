#include "Game.h"
#include "raylib.h"
#include "Entitys/Player.h"
#include "Entitys/Enemy.h"
#include "Entitys/Bullet.h"
#include "vector"

int screenWidth = 800;
int screenHeight = 600;

std::vector<Entity::Bullet> bullets;

void Game::runGame()
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

        if (enemy.hitBox.x + enemy.hitBox.width > screenWidth || enemy.hitBox.x < 0)
        {
            Entity::enemyChangeDir(enemy);
            Entity::enemyGoDown(enemy);
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

}