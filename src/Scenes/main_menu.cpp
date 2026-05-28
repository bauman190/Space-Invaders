#include "main_menu.h"

#include "raylib.h"

#include "UI/button.h"
#include "Game/gameManager.h"

extern GM::gameManager gamemanager;

static Texture backGround;

static UI::Button play;

static UI::Button credits;

static UI::Button controls;

static UI::Button Exit;


void main_menu::checkImputMainMenu()
{
	if (UI::clickButton(play))
	{
		StopMusicStream(gamemanager.music);
		PlayMusicStream(gamemanager.music);
		gamemanager.currentScreen = scenes::Gameplay;
	}
	if (UI::clickButton(credits))
	{
		StopMusicStream(gamemanager.music);
		PlayMusicStream(gamemanager.music);
		gamemanager.currentScreen = scenes::Credits;
	}
	if (UI::clickButton(controls))
	{
		StopMusicStream(gamemanager.music);
		PlayMusicStream(gamemanager.music);
		gamemanager.currentScreen = scenes::HowToPlay;
	}
	if (UI::clickButton(Exit))
	{
		gamemanager.exitGame = true;
	}
}


void main_menu::drawMainMenu()
{
	DrawTexture(backGround, 0, 0, WHITE);
	
	UI::drawButton(play);
	UI::drawButton(credits);
	UI::drawButton(controls);
	UI::drawButton(Exit);

}

void main_menu::inItMainMenu()
{
	float midScreenX = static_cast<float>(GetScreenWidth() / 2);

	UI::inItButton(play, midScreenX,
		static_cast<float>(GetScreenHeight() / 2), 
		LoadTexture("res/Play_on.png"), 
		LoadTexture("res/Play_off.png"));

	UI::inItButton(credits, midScreenX, 
		play.button.y + play.button.height * 2, 
		LoadTexture("res/Credits_on.png"), 
		LoadTexture("res/Credits_off.png"));

	UI::inItButton(controls, midScreenX,
		credits.button.y + credits.button.height * 2,
		LoadTexture("res/Controls_on.png"),
		LoadTexture("res/Controls_off.png"));

	UI::inItButton(Exit, 100, GetScreenHeight() - 50.0f, LoadTexture("res/Exit_on.png"), LoadTexture("res/Exit_off.png"));

	gamemanager.music = LoadMusicStream("res/Asteroids_menu.wav");
	gamemanager.music.looping = true;
	PlayMusicStream(gamemanager.music);
	backGround = LoadTexture("res/MMBG.png");
	backGround.height = GetScreenHeight();
	backGround.width = GetScreenWidth();
}

void main_menu::unloadMianMenu()
{
	UI::unloadButtonTextures(play);
	UI::unloadButtonTextures(Exit);
	UI::unloadButtonTextures(credits);
	UI::unloadButtonTextures(controls);
	UnloadMusicStream(gamemanager.music);
	UnloadTexture(backGround);
}

void main_menu::runMainMenu()
{
	main_menu::checkImputMainMenu();
	UpdateMusicStream(gamemanager.music);

	BeginDrawing();

	ClearBackground(BLACK);
	main_menu::drawMainMenu();
	EndDrawing();
}