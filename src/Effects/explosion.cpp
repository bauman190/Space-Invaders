#include "Explosion.h"

static Texture explosionTexture;
static Sound explosionSound;

void Effects::inItExplosion()
{
    explosionTexture = LoadTexture("res/Explosion.png");
    explosionSound = LoadSound("res/Explosion.wav");
}


    void Effects::UpdateExplosion(Explosion& explosion)
    {
        if (explosion.finished)
            return;


        explosion.frameCounter += GetFrameTime();

        if (explosion.frameCounter >= explosion.frameDuration)
        {

            explosion.frameCounter -= explosion.frameDuration;
            explosion.currentFrame++;
            if (explosion.currentFrame >= explosion.nFrames)
            {
                explosion.finished = true;
            }
            else
            {
                explosion.frameRec.x = explosion.currentFrame * explosion.frameRec.width;
            }
        }
    }

    void Effects::drawExplosion(Explosion expl)
    {
        if (!expl.finished)
        {
            DrawTextureRec(explosionTexture, expl.frameRec, expl.pos, WHITE);
        }
    }

    void Effects::StartExplosion(Explosion& expl, Vector2 pos)
    {
        expl.pos = pos;

        expl.currentFrame = 0;
        expl.frameCounter = 0;
        expl.finished = false;
        expl.frameDuration = 0.2f;
        expl.nFrames = 9.0f;

        expl.frameRec.x = 0;
        expl.frameRec.y = 0;
        expl.frameRec.width = explosionTexture.width / expl.nFrames;
        expl.frameRec.height = explosionTexture.height;
        PlaySound(explosionSound);
    }

    void Effects::unloadExplosion()
    {
        UnloadTexture(explosionTexture);
        UnloadSound(explosionSound);
    }
    
