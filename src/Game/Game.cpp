#include "Game.h"
#include "raylib.h"

#include "Scenes/gameplay.h"
#include "gameManager.h"
#include "Scenes/gameover.h"
#include <ctime>


GM::gameManager gamemanager;

void Game::runGame()
{
    srand(time(NULL));

    InitWindow(gamemanager.screenWidth, gamemanager.screenHeight, "Space Invaders");

    gameplay::initGamePlay();
    gameover::initGameOver();

    while (!WindowShouldClose())
    {
        switch (gamemanager.currentScreen)
        {
        case scenes::MainMenu:
            break;
        
        case scenes::Gameplay:
            gameplay::runGamePlay();
            break;

        case scenes::Pause:
            break;
        
        case scenes::GameOver:
            gameover::runGameOver();
            break;

        case scenes::Credits:
            break;

        case scenes::HowToPlay:
            break;
        default:
            break;
        }
    }

    CloseWindow();

}

