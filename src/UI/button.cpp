#include "UI/button.h"

#include "raylib.h"

static Sound buttonSound;

static bool onButton(UI::Button button);

bool UI::clickButton(Button button)
{

	if (CheckCollisionPointRec(GetMousePosition(), button.button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		PlaySound(buttonSound);
		return true;
	}
	return false;
}

void UI::drawButton(Button button)
{

	if (onButton(button))
	{
		DrawTexture(button.on, static_cast<int>(button.button.x), static_cast<int>(button.button.y), WHITE);
	}
	else
	{
		DrawTexture(button.off, static_cast<int>(button.button.x), static_cast<int>(button.button.y), WHITE);
	}
}

void UI::inItButton(Button& button, float x, float y, Texture on, Texture off)
{
	button.button.width = 150;
	button.button.height = 50;
	button.button.x = x - button.button.width / 2;
	button.button.y = y;
	button.on = on; 
	button.off = off; 
	button.off.width = static_cast<int>(button.button.width);
	button.off.height = static_cast<int>(button.button.height);
	button.on.width = static_cast<int>(button.button.width);
	button.on.height = static_cast<int>(button.button.height);
	buttonSound = LoadSound("res/Button.wav");
}

void UI::unloadButtonTextures(Button& button)
{
	UnloadTexture(button.off);
	UnloadTexture(button.on);
}

static bool onButton(UI::Button button)
{

	if (CheckCollisionPointRec(GetMousePosition(), button.button))
	{
		return true;
	}
	return false;
}