#include "gameplay.h"
#include "Scenes/gameplay_screen_internal.h"

#include "raylib.h"

#include "Entitys/Player.h"
#include "Entitys/Enemy.h"
#include "Entitys/Bullet.h"
#include "vector"
#include "Game/gameManager.h"
#include "UI/button.h"
#include "Effects/Explosion.h"
#include "Entitys/Shield.h"


extern GM::gameManager gamemanager;

static UI::Button Play;
static UI::Button Exit;

static Texture backGround;

static std::vector<Effects::Explosion> explosions;

void gameplay::initGamePlay()
{
    gamemanager.enemys.clear();
    gamemanager.bullets.clear();
    gamemanager.enemysBullets.clear();
    gamemanager.shields.clear();
    gamemanager.gamePaused = false;
    Entity::initPlayer(gamemanager.player);
    UI::inItButton(Play, gamemanager.screenWidth / 2, gamemanager.screenHeight * 0.6, LoadTexture("res/Play_on.png"), LoadTexture("res/PLay_off.png"));
    UI::inItButton(Exit, gamemanager.screenWidth / 2, gamemanager.screenHeight * 0.8, LoadTexture("res/Exit_on.png"), LoadTexture("res/Exit_off.png"));
    backGround = LoadTexture("res/space.png");
    backGround.height = GetScreenHeight();
    backGround.width = GetScreenWidth();
    Effects::inItExplosion();

    gsi::creatEnemys();
    gsi::createShields();
}

void gameplay::runGamePlay()
{

    gsi::updateGamePlay(gamemanager.enemyWallCooldown, gamemanager.enemyShootTimer);
    UpdateMusicStream(gamemanager.music);

    BeginDrawing();

    ClearBackground(BLACK);

    gsi::drawGamePlay();

    EndDrawing();
}

void gameplay::restarGamePlay()
{
    gamemanager.enemys.clear();
    gamemanager.bullets.clear();
    gamemanager.enemysBullets.clear();
    gamemanager.shields.clear();
    explosions.clear();
    gamemanager.rowIncrease = 0;
    gsi::creatEnemys();
    gsi::createShields();
    gamemanager.gamePaused = false;
    Entity::initPlayer(gamemanager.player);
    UnloadMusicStream(gamemanager.music);
    gamemanager.music = LoadMusicStream("res/Asteroids Gameplay.wav");
    gamemanager.music.looping = true;
    PlayMusicStream(gamemanager.music);
}

void gameplay::unloadGameplay()
{
    Entity::unloadEnemyTexture();
    Entity::unloadPlayer();
    Entity::unloadBullet();
    UI::unloadButton(Play);
    UI::unloadButton(Exit);
    UnloadTexture(backGround);
    Effects::unloadExplosion();
}

bool gsi::collisionRecRec(Rectangle r1, Rectangle r2)
{
    return (r1.x < r2.x + r2.width &&
        r1.x + r1.width > r2.x &&
        r1.y < r2.y + r2.height &&
        r1.y + r1.height > r2.y);
}

void gsi::creatEnemys()
{
    const int rows = 1 + gamemanager.rowIncrease;
    const int columns = 10;
    const float spacing = 10.0f;

    Entity::Enemy newEnemy;
    Entity::initEnemy(newEnemy, 0, 0);

    float enemyWidth = newEnemy.hitBox.width;
    float enemyHeight = newEnemy.hitBox.height;

    float formationWidth = columns * enemyWidth + (columns - 1) * spacing;

    float startX = (gamemanager.screenWidth - formationWidth) / 2.0f;
    float startY = gamemanager.screenHeight * 0.1f;

    gamemanager.enemys.clear();

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < columns; col++)
        {
            newEnemy.hitBox.x = startX + col * (enemyWidth + spacing);
            newEnemy.hitBox.y = startY + row * (enemyHeight + spacing);

            gamemanager.enemys.push_back(newEnemy);
        }
    }
}

void gsi::changeAllEnemysDir()
{
    for (size_t i = 0; i < gamemanager.enemys.size(); i++)
    {
        Entity::enemyChangeDir(gamemanager.enemys[i]);
        Entity::enemyGoDown(gamemanager.enemys[i]);
    }
}

void gsi::handleColEnemyWall(float& enemyWallCooldown)
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

void gsi::collisionEnemyBullet()
{
    if (!gamemanager.enemys.empty() && !gamemanager.bullets.empty())
    {
        for (int i = gamemanager.bullets.size() - 1; i >= 0; i--)
        {
            for (int j = gamemanager.enemys.size() - 1; j >= 0; j--)
            {
                if (collisionRecRec(gamemanager.enemys[j].hitBox, gamemanager.bullets[i].hitBox))
                {
                    Effects::Explosion expl;
                    Effects::StartExplosion(expl,{ gamemanager.enemys[j].hitBox.x , gamemanager.enemys[j].hitBox.y });
                    explosions.push_back(expl);

                    gamemanager.enemys.erase(gamemanager.enemys.begin() + j);
                    gamemanager.bullets.erase(gamemanager.bullets.begin() + i);
                    Entity::increasScore(gamemanager.player);

                    break;
                }
            }
        }
    }
}

void gsi::erasBulletsOutOfMap()
{
    for (int i = gamemanager.bullets.size() - 1; i >= 0; i--)
    {
        if (gamemanager.bullets[i].hitBox.y <= 0)
        {
            gamemanager.bullets.erase(gamemanager.bullets.begin() + i);
        }
    }
}

void gsi::updateEnemys()
{
    for (size_t i = 0; i < gamemanager.enemys.size(); i++)
    {
        Entity::updateEnemy(gamemanager.enemys[i]);
    }
}

void gsi::updateBullets()
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

void gsi::handleEnemyRespawn()
{
    if (gamemanager.enemys.empty())
    {
        int maxRowIncrease = 5;
        if (gamemanager.rowIncrease < maxRowIncrease)
        {
            gamemanager.rowIncrease++;
        }
        gamemanager.bullets.clear();
        creatEnemys();
    }
}

void gsi::updateGamePlay(float& enemyWallCooldown, float& enemyShootTimer)
{
    handlePauseInput();
    if (!gamemanager.gamePaused)
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
        updateExplosions();
        colShieldBullet(gamemanager.bullets);
        colShieldBullet(gamemanager.enemysBullets);
        colShieldEnemy();
    }
    if (gamemanager.gamePaused)
    {
        handlePause();
    }
}

void gsi::drawGamePlay()
{
    DrawTexture(backGround, 0, 0, WHITE);
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
    drawExplosions();
    drawShields();
    DrawText(TextFormat("Score: %01i", gamemanager.player.score), 0, 0, 20, BLUE);
    DrawText(TextFormat("Lives: %01i", gamemanager.player.HP), 0, 20, 20, BLUE);

    if (gamemanager.gamePaused)
    {
        const float alpha = 0.2;
        DrawRectangle(0, 0, gamemanager.screenWidth, gamemanager.screenHeight, Fade(BLACK,alpha));
        DrawText("Pause", gamemanager.screenWidth / 2 - MeasureText("Pause", 50) / 2, gamemanager.screenHeight * 0.1, 50, WHITE);
        UI::drawButton(Play);
        UI::drawButton(Exit);
    }
}

void gsi::handleEnemyShoot(float& enemyShootTimer)
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

void gsi::collisionPlayerBullet()
{
    if (!gamemanager.enemysBullets.empty())
    {
        for (int i = gamemanager.enemysBullets.size() - 1; i >= 0; i--)
        {
            if (collisionRecRec(gamemanager.enemysBullets[i].hitBox, gamemanager.player.hitBox))
            {
                gamemanager.enemysBullets.erase(gamemanager.enemysBullets.begin() + i);
                gamemanager.player.HP--;
                PlaySound(gamemanager.player.hitSound);
                break;
            }

        }
    }
}

bool gsi::colPlayerEnemy()
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

void gsi::handelLoseCondition()
{
    if (gamemanager.player.HP <= 0 || colPlayerEnemy())
    {
        gameplay::restarGamePlay();
        StopMusicStream(gamemanager.music);
        UnloadMusicStream(gamemanager.music);
        gamemanager.music = LoadMusicStream("res/Last_Life_Spent.wav");
        PlayMusicStream(gamemanager.music);
        gamemanager.currentScreen = scenes::GameOver;
    }
}

void gsi::togglePause()
{
    gamemanager.gamePaused = !gamemanager.gamePaused;
    if (gamemanager.gamePaused)
    {
        PauseMusicStream(gamemanager.music);
    }
    else
    {
        ResumeMusicStream(gamemanager.music);
    }
}

void gsi::handlePauseInput()
{
    if (IsKeyPressed(KEY_P))
    {
        togglePause();
    }
}

void gsi::handlePause()
{
    if (UI::clickButton(Play))
    {
        togglePause();
    }

    if (UI::clickButton(Exit))
    {
        gamemanager.currentScreen = scenes::MainMenu;
        StopMusicStream(gamemanager.music);
        UnloadMusicStream(gamemanager.music);
        gamemanager.music = LoadMusicStream("res/Asteroids_menu.wav");
        PlayMusicStream(gamemanager.music);
    }
}

void gsi::updateExplosions()
{
    for (int i = 0; i < explosions.size(); i++)
    {
        UpdateExplosion(explosions[i]);
    }
    explosions.erase(std::remove_if(explosions.begin(), explosions.end(), [](const Effects::Explosion& expl)
            {
                return expl.finished;
            }),
        explosions.end());
}

void gsi::drawExplosions()
{
    for (int i = 0; i < explosions.size(); i++)
    {
        drawExplosion(explosions[i]);
    }
}

void gsi::createShields()
{
    gamemanager.shields.clear();
    const int numShields = 5;
    float spacing = GetScreenWidth() / static_cast<float>(numShields + 1);

    Entity::Shield newShield;

    for (int i = 0; i < numShields; i++)
    {
        float x = spacing * (i + 1);
        float y = GetScreenHeight() * 0.8f;

        Entity::inItShield(newShield, x, y);
        gamemanager.shields.push_back(newShield);
    }
}

void gsi::drawShields()
{
    for (int i = 0; i < gamemanager.shields.size(); i++)
    {
        Entity::drawShield(gamemanager.shields[i]);
    }
}

void gsi::colShieldBullet(std::vector<Entity::Bullet>& bullets)
{
    if (!bullets.empty() && !gamemanager.shields.empty())
    {
        for (int i = bullets.size() - 1; i >= 0; i--)
        {
            for (int j = gamemanager.shields.size() -1 ; j >= 0; j--)
            {
                if (collisionRecRec(bullets[i].hitBox, gamemanager.shields[j].hitbox))
                {
                   Entity::takeDamage(gamemanager.shields[j]);

                    if (gamemanager.shields[j].hp <= 0)
                    {
                        Entity::unloadShield(gamemanager.shields[j]);
                        gamemanager.shields.erase(gamemanager.shields.begin() + j);
                    }
                    bullets.erase(bullets.begin() + i);
                    break;
                }
            }
        }
    }
    
}

void gsi::colShieldEnemy()
{
    if (!gamemanager.enemys.empty() && !gamemanager.shields.empty())
    {
        for (int i = gamemanager.enemys.size() - 1; i >= 0; i--)
        {
            for (int j = gamemanager.shields.size() - 1; j >= 0; j--)
            {
                if (collisionRecRec(gamemanager.enemys[i].hitBox, gamemanager.shields[j].hitbox))
                {
                    Entity::takeDamage(gamemanager.shields[j]);

                    if (gamemanager.shields[j].hp <= 0)
                    {
                        Entity::unloadShield(gamemanager.shields[j]);
                        gamemanager.shields.erase(gamemanager.shields.begin() + j);
                    }
                    Effects::Explosion expl;
                    Effects::StartExplosion(expl, { gamemanager.enemys[i].hitBox.x , gamemanager.enemys[i].hitBox.y });
                    explosions.push_back(expl);

                    gamemanager.enemys.erase(gamemanager.enemys.begin() + i);
                    break;
                }
            }
        }
    }
}
