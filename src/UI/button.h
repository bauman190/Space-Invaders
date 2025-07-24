#pragma once
#include "raylib.h"


namespace UI
{ 
struct Button
{
    Rectangle button;
    Texture off;
    Texture on;
};

bool clickButton(Button button);

void drawButton(Button button);

void inItButton(Button& button, float x, float y, Texture on, Texture off);

void unloadButtonTextures(Button& button);
}


    