#pragma once
#include "raylib.h"


namespace Effects
{

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

void inItExplosion();
void UpdateExplosion(Explosion& explosion);
void drawExplosion(Explosion expl);
void StartExplosion(Explosion& expl, Vector2 pos);
void unloadExplosion();
}