#include "Game.h"
#include "raylib.h"
#include "Entitys/Player.h"
#include "Entitys/Enemy.h"
#include "Entitys/Bullet.h"
#include "vector"

int screenWidth = 800;
int screenHeight = 600;

std::vector<Entity::Bullet> bullets;
std::vector <Entity::Enemy> enemys;

static bool collisionRecRec(Rectangle r1, Rectangle r2)
{
    return (r1.x < r2.x + r2.width &&
        r1.x + r1.width > r2.x &&
        r1.y < r2.y + r2.height &&
        r1.y + r1.height > r2.y);
}

static void creatEnemys();

static void handleColEnemyWall(const float enemyWallCooldownTime, float& enemyWallCooldown);

void Game::runGame()
{

    InitWindow(screenWidth, screenHeight, "Space Invaders");

    Entity::Player player;
    Entity::initPlayer(player);
    float enemyWallCooldown = 0.0f;
    const float enemyWallCooldownTime = 1.0f;

    creatEnemys();

    while (!WindowShouldClose())
    {
        Entity::updatePlayer(player);

        for (size_t i = 0; i < enemys.size(); i++)
        {
            Entity::updateEnemy(enemys[i]);
        }              

        for (size_t i = 0; i < bullets.size(); i++)
        {
            Entity::updateBullet(bullets[i]);
        }

        handleColEnemyWall(enemyWallCooldownTime, enemyWallCooldown);

        if (!enemys.empty() && !bullets.empty())
        {
            for (int i = bullets.size() - 1; i >= 0; i--)
            {
                for (int j = enemys.size() - 1; j >= 0; j--)
                {
                    if (collisionRecRec(enemys[j].hitBox, bullets[i].hitBox))
                    {
                        enemys.erase(enemys.begin() + j);
                        bullets.erase(bullets.begin() + i);
                        break;
                    }
                }
            }
        }

        for (int i = bullets.size() - 1; i >= 0; i--)
        {
            if (bullets[i].hitBox.y <= 0)
            {
                bullets.erase(bullets.begin() + i);
            }
        }
        BeginDrawing();

        ClearBackground(BLACK);

        Entity::drawPlayer(player);
  
        for (size_t i = 0; i < enemys.size(); i++)
        {
            Entity::drawEnemy(enemys[i]);
        }
            

        for (size_t i = 0; i < bullets.size(); i++)
        {
            Entity::drawBullet(bullets[i]);
        }

        EndDrawing();
    }

    CloseWindow();

}

static void creatEnemys()
{
    const int rows = 5;
    const int columns = 15;

    Entity::Enemy newEnemy;

    Entity::initEnemy(newEnemy, screenWidth * 0.2, screenHeight * 0.1f);

    enemys.push_back(newEnemy);

   float initialX = newEnemy.hitBox.x;

    for (size_t j = 0; j < rows; j++)
    {
        newEnemy.hitBox.x = initialX;
        if (j >= 1)
        {
            newEnemy.hitBox.y += newEnemy.hitBox.height + 10;
        }

        enemys.push_back(newEnemy);

        for (int i = 1; i < columns; i++)
        {
            newEnemy.hitBox.x += enemys[i - 1].hitBox.width + 10;
            enemys.push_back(newEnemy);
        }
    }
}

static void changeAllEnemysDir()
{
    for (size_t i = 0; i < enemys.size(); i++)
    {
        Entity::enemyChangeDir(enemys[i]);
        Entity::enemyGoDown(enemys[i]);
    }
}

#include <iostream>
static void handleColEnemyWall(const float enemyWallCooldownTime, float& enemyWallCooldown)
{
    if (enemyWallCooldown > 0.0f)
    {
        enemyWallCooldown -= GetFrameTime();
    }
    if (enemyWallCooldown > 0.0f)
    {
        return;
    }

    for (size_t i = 0; i < enemys.size(); i++)
    {
        if (enemys[i].hitBox.x + enemys[i].hitBox.width > screenWidth || enemys[i].hitBox.x < 0)
        {
            std::cout << "Colisión detectada - Cambiando dirección y bajando\n";
            enemyWallCooldown = enemyWallCooldownTime;
            changeAllEnemysDir();
            break;
        }
    }  
}