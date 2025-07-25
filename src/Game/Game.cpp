#include "Game.h"
#include "raylib.h"

#include "Scenes/gameplay.h"
#include "gameManager.h"
#include <time.h>

GM::gameManager gamemanager;

void Game::runGame()
{
    srand(time(NULL));

    InitWindow(gamemanager.screenWidth, gamemanager.screenHeight, "Space Invaders");

    gameplay::initGamePlay();

    while (!WindowShouldClose())
    {
        gameplay::runGamePlay();
    }

    CloseWindow();

}

