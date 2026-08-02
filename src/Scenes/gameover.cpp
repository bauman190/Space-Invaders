#include "gameover.h"

#include "raylib.h"

#include "Game/gameManager.h"
#include "UI/button.h"
#include "Scenes/screen_options.h"
#include "gameplay.h"

extern GM::gameManager gamemanager;

static UI::Button play;
static UI::Button back;
static Texture backGround;

static void drawGameOver()
{
	DrawTexture(backGround, 0, 0, WHITE);

	UI::drawButton(play);
	UI::drawButton(back);
}

static void updateGameOver()
{
	if (UI::clickButton(play))
	{
		gamemanager.currentScreen = scenes::Gameplay;
		gameplay::restarGamePlay();
	}

	if (UI::clickButton(back))
	{
		gamemanager.currentScreen = scenes::MainMenu;
		StopMusicStream(gamemanager.music);
		UnloadMusicStream(gamemanager.music);
		gamemanager.music = LoadMusicStream("res/Asteroids_menu.wav");
		PlayMusicStream(gamemanager.music);	
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
	UI::inItButton(play, gamemanager.screenWidth * 0.3, gamemanager.screenHeight * 0.7, LoadTexture("res/Play_on.png"), LoadTexture("res/Play_off.png"));
	UI::inItButton(back, gamemanager.screenWidth * 0.7, gamemanager.screenHeight * 0.7, LoadTexture("res/Back_on.png"), LoadTexture("res/Back_off.png"));
	backGround = LoadTexture("res/GameOver.png");
	backGround.height = gamemanager.screenHeight;
	backGround.width = gamemanager.screenWidth;
}

void gameover::unloadGameOver()
{
	UI::unloadButton(play);
	UI::unloadButton(back);
}