#pragma once
#include "raylib.h"

struct Explosion
{
    Vector2 pos;
    Rectangle frameRec;
    int currentFrame;
    float frameCounter;
    bool finished;
    int nFrames;
    float frameDuration;
};