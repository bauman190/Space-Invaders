#include "gameplay.h"

#include "raylib.h"

#include "Entitys/Player.h"
#include "Entitys/Enemy.h"
#include "Entitys/Bullet.h"
#include "vector"
#include "Game/gameManager.h"
#include "UI/button.h"
#include "Effects/Explosion.h"

extern GM::gameManager gamemanager;

static UI::Button Play;
static UI::Button Exit;

static Texture backGround;

static Texture explosionTexture;
static Sound explosionSound;

static std::vector<Explosion> explosions;

static void updateExplosions();
static void drawExplosions();

static void StartExplosion(Explosion& expl, Vector2 pos);

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

static void handlePauseInput();

static void handlePause();

static void creatEnemys()
{
    const int rows = 3;
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
                    Explosion expl;
                    StartExplosion(expl,{ gamemanager.enemys[j].hitBox.x , gamemanager.enemys[j].hitBox.y });
                    explosions.push_back(expl);

                    gamemanager.enemys.erase(gamemanager.enemys.begin() + j);
                    gamemanager.bullets.erase(gamemanager.bullets.begin() + i);
                    Entity::increasScore(gamemanager.player);

                    PlaySound(explosionSound);
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
    }
    if (gamemanager.gamePaused)
    {
        handlePause();
    }
}

static void drawGamePlay()
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

void gameplay::initGamePlay()
{
    gamemanager.enemys.clear();
    gamemanager.bullets.clear();
    gamemanager.enemysBullets.clear();
    gamemanager.gamePaused = false;
    Entity::initPlayer(gamemanager.player);
    UI::inItButton(Play, gamemanager.screenWidth / 2, gamemanager.screenHeight * 0.6, LoadTexture("res/Play_on.png"), LoadTexture("res/PLay_off.png"));
    UI::inItButton(Exit, gamemanager.screenWidth / 2, gamemanager.screenHeight * 0.8, LoadTexture("res/Exit_on.png"), LoadTexture("res/Exit_off.png"));
    backGround = LoadTexture("res/space.png");
    backGround.height = GetScreenHeight();
    backGround.width = GetScreenWidth();
    explosionTexture = LoadTexture("res/Explosion.png");
    explosionSound = LoadSound("res/Explosion.wav");

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
    UpdateMusicStream(gamemanager.music);

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

static void togglePause()
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

static void handlePauseInput()
{
    if (IsKeyPressed(KEY_P))
    {
        togglePause();
    }
}

static void handlePause()
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

void gameplay::restarGamePlay()
{
    gamemanager.enemys.clear();
    gamemanager.bullets.clear();
    gamemanager.enemysBullets.clear();
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
    Entity::unloadPlayerTexture();
    Entity::unloadBullet();
    UI::unloadButton(Play);
    UI::unloadButton(Exit);
    UnloadTexture(backGround);
    UnloadTexture(explosionTexture);
    UnloadSound(explosionSound);
}

static void UpdateExplosion(Explosion& explosion)
{
    if (explosion.finished)
        return;

    
    explosion.frameCounter += GetFrameTime();
    
    if (explosion.frameCounter >= explosion.frameDuration)
    {
        
        explosion.frameCounter -= explosion.frameDuration;
        explosion.currentFrame++; 
        if (explosion.currentFrame >= explosion.nFrames) 
        { 
            explosion.finished = true; 
        }
        else
        {
            explosion.frameRec.x = explosion.currentFrame * explosion.frameRec.width;
        }
    }
}

static void drawExplosion(Explosion expl)
{
    if (!expl.finished)
    {
        DrawTextureRec(explosionTexture, expl.frameRec, expl.pos, WHITE);
    }
}

static void StartExplosion(Explosion& expl, Vector2 pos)
{
    expl.pos = pos;

    expl.currentFrame = 0;
    expl.frameCounter = 0;
    expl.finished = false;
    expl.frameDuration = 0.2f;
    expl.nFrames = 9.0f;

    expl.frameRec.x = 0;
    expl.frameRec.y = 0;
    expl.frameRec.width = explosionTexture.width / expl.nFrames;
    expl.frameRec.height = explosionTexture.height;
}

static void updateExplosions()
{
    for (int i = 0; i < explosions.size(); i++)
    {
        UpdateExplosion(explosions[i]);
    }
    explosions.erase(std::remove_if(explosions.begin(), explosions.end(), [](const Explosion& expl)
            {
                return expl.finished;
            }),
        explosions.end());
}

static void drawExplosions()
{
    for (int i = 0; i < explosions.size(); i++)
    {
        drawExplosion(explosions[i]);
    }
}
