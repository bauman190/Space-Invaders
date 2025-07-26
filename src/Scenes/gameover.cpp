#include "gameover.h"

#include "raylib.h"

#include "Game/gameManager.h"
#include "UI/button.h"
#include "Scenes/screen_options.h"
#include "gameplay.h"

extern GM::gameManager gamemanager;

static UI::Button play;

static void drawGameOver()
{

	DrawText("GAME OVER", gamemanager.screenWidth / 2 - MeasureText("Game Over", 50) / 2, gamemanager.screenHeight * 0.2, 50, WHITE);

	UI::drawButton(play);
}

static void updateGameOver()
{
	if (UI::clickButton(play))
	{
		gamemanager.currentScreen = scenes::Gameplay;
		gameplay::initGamePlay();
	}
}

void gameover::runGameOver()
{
	updateGameOver();

	BeginDrawing();

	ClearBackground(BLACK);

	drawGameOver();

	EndDrawing();
}

void gameover::initGameOver()
{
	UI::inItButton(play, gamemanager.screenWidth / 2, gamemanager.screenHeight / 2, LoadTexture("res/Play_on.png"), LoadTexture("res/Play_off.png"));
}