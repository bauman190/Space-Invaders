#pragma once
#include "raylib.h"
#include "Entitys/Bullet.h"
#include <vector>


namespace gsi
{
	bool collisionRecRec(Rectangle r1, Rectangle r2);

	void creatEnemys();

	void changeAllEnemysDir();

	void handleColEnemyWall(float& enemyWallCooldown);

	void collisionEnemyBullet();

	void erasBulletsOutOfMap();

	void updateEnemys();

	void updateBullets();

	void handleEnemyRespawn();

	void updateGamePlay(float& enemyWallCooldown, float& enemyShootTimer);

	void drawGamePlay();

	void handleEnemyShoot(float& enemyShootTimer);

	void collisionPlayerBullet();

	bool colPlayerEnemy();

	void handelLoseCondition();

	void togglePause();

	void handlePauseInput();

	void handlePause();

	void updateExplosions();

	void drawExplosions();

	void createShields();

	void drawShields();

	void colShieldBullet(std::vector<Entity::Bullet>& bullets);

	void colShieldEnemy();
}