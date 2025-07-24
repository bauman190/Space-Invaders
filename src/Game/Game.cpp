#include "Game.h"
#include "raylib.h"

#include "Scenes/screen_options.h"
#include "Scenes/gameplay.h"

int screenWidth = 800;
int screenHeight = 600;

/*std::vector<Entity::Bullet> bullets;
std::vector <Entity::Enemy> enemys;
std::vector<Entity::Bullet> enemysBullets;*/

void Game::runGame()
{

    InitWindow(screenWidth, screenHeight, "Space Invaders");

    gameplay::initGamePlay();

    while (!WindowShouldClose())
    {
        gameplay::runGamePlay();
    }

    CloseWindow();

}

