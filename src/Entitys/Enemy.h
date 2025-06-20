#pragma once
#include "raylib.h"

namespace Entity
{
	struct Enemy
	{
		Rectangle hitBox;
		float speed;
	};
	void drawEnemy(Enemy enemy);
	void updateEnemy(Enemy& enemy);
	void initEnemy(Enemy& enemy, float x, float y);
}