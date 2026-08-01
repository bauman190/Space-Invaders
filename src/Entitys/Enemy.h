#pragma once
#include "raylib.h"
#include "Tools/TextureInfo.h"

namespace Entity
{
	struct Enemy
	{
		Rectangle hitBox;
		float speed;
		tools::textureInfo texture;
	};
	void drawEnemy(Enemy enemy);
	void updateEnemy(Enemy& enemy);
	void initEnemy(Enemy& enemy, float x, float y);
	void enemyChangeDir(Enemy& enemy);
	void enemyGoDown(Enemy& enemy);
	void enemyShoot(Enemy enemy);
	void unloadEnemyTexture();
	void createEnemy(Enemy& enemy, float x, float y);
}