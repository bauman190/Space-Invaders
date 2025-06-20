#pragma once
#include "raylib.h"

namespace Entity
{
	struct Bullet
	{
		Rectangle hitBox;
		float speed;
	};
	void drawBullet(Bullet bullet);
	void updateBullet(Bullet& bullet);
	Bullet initBullet(float x, float y);
}