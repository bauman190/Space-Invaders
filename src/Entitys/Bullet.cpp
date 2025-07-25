#include "Bullet.h"

#include "raylib.h"


void Entity::drawBullet(Bullet bullet)
{
	DrawRectangle(static_cast<int>(bullet.hitBox.x),
		static_cast<int>(bullet.hitBox.y),
		static_cast<int>(bullet.hitBox.width),
		static_cast<int>(bullet.hitBox.height),
		WHITE);
}
void Entity::updateBullet(Bullet& bullet)
{
	bullet.hitBox.y -= bullet.speed * GetFrameTime();
}
Entity::Bullet Entity::initBullet(float x, float y)
{
	Bullet bullet;
	bullet.hitBox.width = 5;
	bullet.hitBox.height = bullet.hitBox.width;
	bullet.hitBox.x = x - bullet.hitBox.width / 2;
	bullet.hitBox.y = y;
	bullet.speed = 100.0f;
	return bullet;
}
