#include "credits.h"

#include "raylib.h"

#include "UI/Button.h"
#include "Game/gameManager.h"

extern GM::gameManager gamemanager;

static UI::Button back;

static Texture background;

void credits::inItCredits()
{
	background = LoadTexture("res/space.png");
	background.width = GetScreenWidth();
	background.height = GetScreenHeight();
	UI::inItButton(back, GetScreenWidth() * 0.1f, GetScreenHeight() * 0.9f, LoadTexture("res/Back_on.png"), LoadTexture("res/Back_off.png"));
}

static void drawCredits()
{
	DrawTexture(background, 0, 0, WHITE);

	int x = GetScreenWidth() / 2 - MeasureText("Credits", 50) / 2;
	int y = static_cast<int>(GetScreenHeight() * 0.1);
	DrawText("Credits", x, y, 50, WHITE);
	y = static_cast<int>(GetScreenHeight() * 0.3);
	x = static_cast<int>(GetScreenWidth() * 0.80 - MeasureText("Art: ", 20) / 2);
	DrawText("Art: ", x, y, 20, WHITE);

	x = static_cast<int>(GetScreenWidth() * 0.20 - MeasureText("Code: ", 20) / 2);
	DrawText("Code: ", x, y, 20, WHITE);

	y = static_cast<int>(GetScreenHeight() * 0.4);
	x = static_cast<int>(GetScreenWidth() * 0.80 - MeasureText("Felipe Garea Berlin", 20) / 2);
	DrawText("Felipe Garea Berlin", x, y, 20, GRAY);

	x = static_cast<int>(GetScreenWidth() * 0.20 - MeasureText("Juan Bautista Castignain", 20) / 2);
	DrawText("Juan Bautista Castignain", x, y, 20, GRAY);

	y = static_cast<int>(GetScreenHeight() * 0.5);
	x = static_cast<int>(GetScreenWidth() * 0.80 - MeasureText("Space Ship, Asteroid", 20) / 2);
	DrawText("Space Ship, Asteroid", x, y, 20, GRAY);

	y = static_cast<int>(GetScreenHeight() * 0.6);
	x = static_cast<int>(GetScreenWidth() * 0.80 - MeasureText("Buttons, Background", 20) / 2);
	DrawText("Buttons, Background", x, y, 20, GRAY);

	y = static_cast<int>(GetScreenHeight() * 0.5);
	x = static_cast<int>(GetScreenWidth() * 0.20 - MeasureText("Music and Sound Efects", 20) / 2);
	DrawText("Music and Sound Efects:", x, y, 20, WHITE);

	y = static_cast<int>(GetScreenHeight() * 0.6);
	x = static_cast<int>(GetScreenWidth() * 0.20 - MeasureText("Juan Bautista Castignain", 20) / 2);
	DrawText("Juan Bautista Castignain", x, y, 20, GRAY);

	UI::drawButton(back);
}

static void checkInputCredits()
{
	if (UI::clickButton(back))
	{
		gamemanager.currentScreen = scenes::MainMenu;
	}
}

void credits::unloadCreditsTextures()
{
	UI::unloadButton(back);
}

void credits::runCredits()
{
	checkInputCredits();
	BeginDrawing();

	ClearBackground(BLACK);
	drawCredits();
	EndDrawing();
}