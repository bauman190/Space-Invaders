#include "gameplay.h"

#include "raylib.h"

#include "Entitys/Player.h"
#include "Entitys/Enemy.h"
#include "Entitys/Bullet.h"
#include "vector"
#include "screen_options.h"

extern int screenWidth;
extern int screenHeight;

//scenes::inGameScene inGameStatus = scenes::Game;

std::vector<Entity::Bullet> bullets;
std::vector <Entity::Enemy> enemys;
std::vector<Entity::Bullet> enemysBullets;
Entity::Player player;

static bool collisionRecRec(Rectangle r1, Rectangle r2)
{
    return (r1.x < r2.x + r2.width &&
        r1.x + r1.width > r2.x &&
        r1.y < r2.y + r2.height &&
        r1.y + r1.height > r2.y);
}

static void creatEnemys();

static void handleColEnemyWall(float& enemyWallCooldown);

static void updateGamePlay(float& enemyWallCooldown, float& enemyShootTimer);

static void drawGamePlay();

static void handleEnemyShoot(float& enemyShootTimer);

static void collisionPlayerBullet();

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
            enemys.push_back(newEnemy);
        }

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

static void handleColEnemyWall(float& enemyWallCooldown)
{
    const float enemyWallCooldownTime = 1.0f;

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
            enemyWallCooldown = enemyWallCooldownTime;
            changeAllEnemysDir();
            break;
        }
    }
}

static void collisionEnemyBullet()
{
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
                    Entity::increasScore(player);
                    break;
                }
            }
        }
    }
}

static void erasBulletsOutOfMap()
{
    for (int i = bullets.size() - 1; i >= 0; i--)
    {
        if (bullets[i].hitBox.y <= 0)
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}

static void updateEnemys()
{
    for (size_t i = 0; i < enemys.size(); i++)
    {
        Entity::updateEnemy(enemys[i]);
    }
}

static void updateBullets()
{
    for (size_t i = 0; i < bullets.size(); i++)
    {
        Entity::updateBullet(bullets[i]);
    }

    for (size_t i = 0; i < enemysBullets.size(); i++)
    {
        Entity::updateBullet(enemysBullets[i]);
    }
}

static void handleEnemyRespawn()
{
    if (enemys.empty())
    {
        bullets.clear();
        creatEnemys();
    }
}

static void updateGamePlay(float& enemyWallCooldown, float& enemyShootTimer)
{

    handleEnemyRespawn();
    Entity::updatePlayer(player);
    updateEnemys();
    updateBullets();
    handleColEnemyWall(enemyWallCooldown);
    collisionEnemyBullet();
    collisionPlayerBullet();
    handleEnemyShoot(enemyShootTimer);
    erasBulletsOutOfMap();

}

static void drawGamePlay()
{
    Entity::drawPlayer(player);

    for (size_t i = 0; i < enemys.size(); i++)
    {
        Entity::drawEnemy(enemys[i]);
    }

    for (size_t i = 0; i < bullets.size(); i++)
    {
        Entity::drawBullet(bullets[i]);
    }

    for (size_t i = 0; i < enemysBullets.size(); i++)
    {
        Entity::drawBullet(enemysBullets[i]);
    }

    DrawText(TextFormat("Score: %01i", player.score), 0, 0, 20, BLUE);
    DrawText(TextFormat("Lives: %01i", player.HP), 0, 20, 20, BLUE);
}

void gameplay::initGamePlay()
{
    Entity::initPlayer(player);

    creatEnemys();
}

static void handleEnemyShoot(float& enemyShootTimer)
{
    const float enemyShootCooldown = 3.0f;

    enemyShootTimer += GetFrameTime();

    if (enemyShootTimer >= enemyShootCooldown)
    {
        if (!enemys.empty())
        {
            Entity::enemyShoot(enemys[rand() % enemys.size()]);
            enemyShootTimer = 0;
        }
        enemyShootTimer = 0.0f;
    }
}

static void collisionPlayerBullet()
{
    if (!enemysBullets.empty())
    {
        for (int i = enemysBullets.size() - 1; i >= 0; i--)
        {
            if (collisionRecRec(enemysBullets[i].hitBox, player.hitBox))
            {
                enemysBullets.erase(enemysBullets.begin() + i);
                player.HP--;
                break;
            }

        }
    }
}

void gameplay::runGamePlay()
{
    //los timers pueden traer bug porque se resetean 
    float enemyWallCooldown = 0.0f;
    //const float enemyWallCooldownTime = 1.0f;
    float enemyShootTimer = 0.0f;

    updateGamePlay(enemyWallCooldown, enemyShootTimer);

    BeginDrawing();

    ClearBackground(BLACK);

    drawGamePlay();

    EndDrawing();
}