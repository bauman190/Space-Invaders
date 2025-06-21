#include "Game.h"
#include "raylib.h"
#include "Entitys/Player.h"
#include "Entitys/Enemy.h"
#include "Entitys/Bullet.h"
#include "vector"

int screenWidth = 800;
int screenHeight = 600;

std::vector<Entity::Bullet> bullets;

static bool collisionRecRec(Rectangle r1, Rectangle r2)
{
    return (r1.x < r2.x + r2.width &&
        r1.x + r1.width > r2.x &&
        r1.y < r2.y + r2.height &&
        r1.y + r1.height > r2.y);
}

void Game::runGame()
{

    InitWindow(screenWidth, screenHeight, "Space Invaders");

    Entity::Player player;
    std::vector <Entity::Enemy> enemys;
    Entity::initPlayer(player);

    Entity::Enemy enemy;

    Entity::initEnemy(enemy, screenWidth / 2, screenHeight * 0.1f);

    enemys.push_back(enemy);

    while (!WindowShouldClose())
    {
        Entity::updatePlayer(player);

        if (!enemys.empty())
        {
            Entity::updateEnemy(enemys[0]);
        }

        for (size_t i = 0; i < bullets.size(); i++)
        {
            Entity::updateBullet(bullets[i]);
        }

        if (!enemys.empty())
        {
            if (enemys[0].hitBox.x + enemys[0].hitBox.width > screenWidth || enemys[0].hitBox.x < 0)
            {
                Entity::enemyChangeDir(enemys[0]);
                Entity::enemyGoDown(enemys[0]);
            }
        }

        for (size_t i = 0; i < bullets.size(); i++)
        {
            if (!enemys.empty())
            {
                if (collisionRecRec(enemys[0].hitBox, bullets[i].hitBox))
                {
                    enemys.erase(enemys.begin());
                    bullets.erase(bullets.begin() + i);
                    i--;
                }
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        Entity::drawPlayer(player);

        if (!enemys.empty())
        {
            Entity::drawEnemy(enemys[0]);
        }

        for (size_t i = 0; i < bullets.size(); i++)
        {
            Entity::drawBullet(bullets[i]);
        }

        EndDrawing();

    }


    CloseWindow();

}