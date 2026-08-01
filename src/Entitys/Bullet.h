#pragma once
#include "raylib.h"

#include "Tools/TextureInfo.h"

namespace Entity
{
	struct Bullet
	{
		Rectangle hitBox;
		float speed;
		tools::textureInfo texture;
	};
	void drawBullet(Bullet bullet);
	void updateBullet(Bullet& bullet);
	Bullet initBullet(float x, float y);
	void unloadBullet();
}