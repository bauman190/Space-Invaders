#pragma once
#include "raylib.h"

namespace Entity
{
	struct Player
	{
		Rectangle hitBox;
		int score;
		int HP;
		int maxHP;
		float speed;
	};
	void drawPlayer(Player player);
	void updatePlayer(Player& player);
	void initPlayer(Player& player);
	void increasScore(Player& player);
}