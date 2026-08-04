#pragma once

#include "raylib.h"

namespace Entity
{

	struct Shield
	{
		Rectangle hitbox;
		int hp;
		Color color;
	};

	void inItShield(Shield& shield , int x, int y);
	void takeDamage(Shield& shield);
	void drawShield(Shield shield);
}
