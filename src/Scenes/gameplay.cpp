#include "gameplay.h"

#include "raylib.h"

#include "Entitys/Player.h"
#include "Entitys/Enemy.h"
#include "Entitys/Bullet.h"
#include "vector"
#include "Game/gameManager.h"

extern GM::gameManager gamemanager;

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

static void handelLoseCondition();

static void creatEnemys()
{
    const int rows = 5;
    const int columns = 15;

    Entity::Enemy newEnemy;

    Entity::initEnemy(newEnemy, gamemanager.screenWidth * 0.2, gamemanager.screenHeight * 0.1f);

    gamemanager.enemys.push_back(newEnemy);

    float initialX = newEnemy.hitBox.x;

    for (size_t j = 0; j < rows; j++)
    {
        newEnemy.hitBox.x = initialX;
        if (j >= 1)
        {
            newEnemy.hitBox.y += newEnemy.hitBox.height + 10;
            gamemanager.enemys.push_back(newEnemy);
        }

        for (int i = 1; i < columns; i++)
        {
            newEnemy.hitBox.x += gamemanager.enemys[i - 1].hitBox.width + 10;
            gamemanager.enemys.push_back(newEnemy);
        }
    }
}

static void changeAllEnemysDir()
{
    for (size_t i = 0; i < gamemanager.enemys.size(); i++)
    {
        Entity::enemyChangeDir(gamemanager.enemys[i]);
        Entity::enemyGoDown(gamemanager.enemys[i]);
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

    for (size_t i = 0; i < gamemanager.enemys.size(); i++)
    {
        if (gamemanager.enemys[i].hitBox.x + gamemanager.enemys[i].hitBox.width > gamemanager.screenWidth || gamemanager.enemys[i].hitBox.x < 0)
        {
            enemyWallCooldown = enemyWallCooldownTime;
            changeAllEnemysDir();
            break;
        }
    }
}

static void collisionEnemyBullet()
{
    if (!gamemanager.enemys.empty() && !gamemanager.bullets.empty())
    {
        for (int i = gamemanager.bullets.size() - 1; i >= 0; i--)
        {
            for (int j = gamemanager.enemys.size() - 1; j >= 0; j--)
            {
                if (collisionRecRec(gamemanager.enemys[j].hitBox, gamemanager.bullets[i].hitBox))
                {
                    gamemanager.enemys.erase(gamemanager.enemys.begin() + j);
                    gamemanager.bullets.erase(gamemanager.bullets.begin() + i);
                    Entity::increasScore(gamemanager.player);
                    break;
                }
            }
        }
    }
}

static void erasBulletsOutOfMap()
{
    for (int i = gamemanager.bullets.size() - 1; i >= 0; i--)
    {
        if (gamemanager.bullets[i].hitBox.y <= 0)
        {
            gamemanager.bullets.erase(gamemanager.bullets.begin() + i);
        }
    }
}

static void updateEnemys()
{
    for (size_t i = 0; i < gamemanager.enemys.size(); i++)
    {
        Entity::updateEnemy(gamemanager.enemys[i]);
    }
}

static void updateBullets()
{
    for (size_t i = 0; i < gamemanager.bullets.size(); i++)
    {
        Entity::updateBullet(gamemanager.bullets[i]);
    }

    for (size_t i = 0; i < gamemanager.enemysBullets.size(); i++)
    {
        Entity::updateBullet(gamemanager.enemysBullets[i]);
    }
}

static void handleEnemyRespawn()
{
    if (gamemanager.enemys.empty())
    {
        gamemanager.bullets.clear();
        creatEnemys();
    }
}

static void updateGamePlay(float& enemyWallCooldown, float& enemyShootTimer)
{

    handleEnemyRespawn();
    Entity::updatePlayer(gamemanager.player);
    updateEnemys();
    updateBullets();
    handleColEnemyWall(enemyWallCooldown);
    collisionEnemyBullet();
    collisionPlayerBullet();
    handleEnemyShoot(enemyShootTimer);
    erasBulletsOutOfMap();
    handelLoseCondition();

}

static void drawGamePlay()
{
    Entity::drawPlayer(gamemanager.player);

    for (size_t i = 0; i < gamemanager.enemys.size(); i++)
    {
        Entity::drawEnemy(gamemanager.enemys[i]);
    }

    for (size_t i = 0; i < gamemanager.bullets.size(); i++)
    {
        Entity::drawBullet(gamemanager.bullets[i]);
    }

    for (size_t i = 0; i < gamemanager.enemysBullets.size(); i++)
    {
        Entity::drawBullet(gamemanager.enemysBullets[i]);
    }

    DrawText(TextFormat("Score: %01i", gamemanager.player.score), 0, 0, 20, BLUE);
    DrawText(TextFormat("Lives: %01i", gamemanager.player.HP), 0, 20, 20, BLUE);
}

void gameplay::initGamePlay()
{
    gamemanager.enemys.clear();
    gamemanager.bullets.clear();
    gamemanager.enemysBullets.clear();
    Entity::initPlayer(gamemanager.player);

    creatEnemys();
}

static void handleEnemyShoot(float& enemyShootTimer)
{
    const float enemyShootCooldown = 3.0f;

    enemyShootTimer += GetFrameTime();

    if (enemyShootTimer >= enemyShootCooldown)
    {
        if (!gamemanager.enemys.empty())
        {
            Entity::enemyShoot(gamemanager.enemys[rand() % gamemanager.enemys.size()]);
            enemyShootTimer = 0;
        }
        enemyShootTimer = 0.0f;
    }
}

static void collisionPlayerBullet()
{
    if (!gamemanager.enemysBullets.empty())
    {
        for (int i = gamemanager.enemysBullets.size() - 1; i >= 0; i--)
        {
            if (collisionRecRec(gamemanager.enemysBullets[i].hitBox, gamemanager.player.hitBox))
            {
                gamemanager.enemysBullets.erase(gamemanager.enemysBullets.begin() + i);
                gamemanager.player.HP--;
                break;
            }

        }
    }
}

void gameplay::runGamePlay()
{

    updateGamePlay(gamemanager.enemyWallCooldown, gamemanager.enemyShootTimer);

    BeginDrawing();

    ClearBackground(BLACK);

    drawGamePlay();

    EndDrawing();
}

static bool colPlayerEnemy()
{
    for (size_t i = 0; i < gamemanager.enemys.size(); i++)
    {
        if (collisionRecRec(gamemanager.enemys[i].hitBox, gamemanager.player.hitBox))
        {
            return true;
        }
    }
    return false;
}

static void handelLoseCondition()
{
    if (gamemanager.player.HP <= 0 || colPlayerEnemy())
    {
        gameplay::initGamePlay();
        gamemanager.currentScreen = scenes::GameOver;
    }
}