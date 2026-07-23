#include "how_to_play.h"

#include "raylib.h"

#include "UI/button.h"
#include "Game/gameManager.h"

extern GM::gameManager gamemanager;

static UI::Button back;

static Texture background;

void how_to_play::inItHowTo()
{
	background = LoadTexture("res/space.png");
	background.width = GetScreenWidth();
	background.height = GetScreenHeight();
	UI::inItButton(back, 100.0f, GetScreenHeight() - 50.0f, LoadTexture("res/Back_on.png"), LoadTexture("res/Back_off.png"));
}
static void drawHowTo()
{
	DrawTexture(background, 0, 0, WHITE);
	UI::drawButton(back);

	int x = GetScreenWidth() / 2 - MeasureText("Controls", 50) / 2;
	int y = static_cast<int>(GetScreenHeight() * 0.1);
	DrawText("Controls", x, y, 50, WHITE);

	x = static_cast<int>(GetScreenWidth() * 0.20);
	y = static_cast<int>(GetScreenHeight() * 0.3);
	DrawText("D: Move Right", x, y, 40, WHITE);

	y = static_cast<int>(GetScreenHeight() * 0.4);
	DrawText("A: Move Left", x, y, 40, WHITE);

	y = static_cast<int>(GetScreenHeight() * 0.5);
	DrawText("Space Bar: Shoot", x, y, 40, WHITE);

	y = static_cast<int>(GetScreenHeight() * 0.6);
	DrawText("P: Pause", x, y, 40, WHITE);

	y = static_cast<int>(GetScreenHeight() * 0.7);
	DrawText("Survive as long as yo can!", x, y, 20, WHITE);
}

static void inputHowTo()
{
	if (UI::clickButton(back))
	{
		gamemanager.currentScreen = scenes::MainMenu;
	}
}

void how_to_play::runHowtoPlay()
{
	inputHowTo();
	BeginDrawing();

	ClearBackground(BLACK);
	drawHowTo();
	EndDrawing();
}

void how_to_play::unloadHowTo()
{
	UI::unloadButtonTextures(back);
}

