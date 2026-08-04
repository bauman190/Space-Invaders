#pragma once

#include "raylib.h"

namespace Entity
{

	struct Shield
	{
		Rectangle hitbox;
		int hp;
		Rectangle sourceRec;
		Texture texture;
	};

	void inItShield(Shield& shield , int x, int y);
	void takeDamage(Shield& shield);
	void drawShield(Shield shield);
	void unloadShield(Shield& shield);
}
