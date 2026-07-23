#include "Game.h"
#include "raylib.h"

#include "Scenes/gameplay.h"
#include "Scenes/main_menu.h"
#include "gameManager.h"
#include "Scenes/gameover.h"
#include "Scenes/how_to_play.h"
#include "Scenes/credits.h"
#include <ctime>


GM::gameManager gamemanager;

void Game::runGame()
{
    srand(time(NULL));

    InitWindow(gamemanager.screenWidth, gamemanager.screenHeight, "Space Invaders");
    InitAudioDevice();
    main_menu::inItMainMenu();
    gameplay::initGamePlay();
    gameover::initGameOver();
    how_to_play::inItHowTo();
    credits::inItCredits();

    while (!WindowShouldClose() && !gamemanager.exitGame)
    {
        switch (gamemanager.currentScreen)
        {
        case scenes::MainMenu:
            main_menu::runMainMenu();
            break;
        
        case scenes::Gameplay:
            gameplay::runGamePlay();
            break;
        
        case scenes::GameOver:
            gameover::runGameOver();
            break;

        case scenes::Credits:
            credits::runCredits();
            break;

        case scenes::HowToPlay:
            how_to_play::runHowtoPlay();
            break;
        default:
            break;
        }
    }
    CloseAudioDevice();
    CloseWindow();

}

