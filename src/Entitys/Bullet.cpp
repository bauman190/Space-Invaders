#include "Bullet.h"

#include "raylib.h"

static Texture bulletTexture;

static Sound bulletSound;

void Entity::drawBullet(Bullet bullet)
{
#ifdef _DEBUG
	DrawRectangle(static_cast<int>(bullet.hitBox.x),
		static_cast<int>(bullet.hitBox.y),
		static_cast<int>(bullet.hitBox.width),
		static_cast<int>(bullet.hitBox.height),
		WHITE);
#endif
	DrawTexturePro(bullet.texture.texture, bullet.texture.source, bullet.texture.dest, { 0, 0 }, 0, WHITE);
}
void Entity::updateBullet(Bullet& bullet)
{
	bullet.hitBox.y -= bullet.speed * GetFrameTime();
	bullet.texture.dest.x = bullet.hitBox.x;
	bullet.texture.dest.y = bullet.hitBox.y;
}
Entity::Bullet Entity::initBullet(float x, float y)
{
	Bullet bullet;
	bullet.hitBox.width = 5;
	bullet.hitBox.height = bullet.hitBox.width;
	bullet.hitBox.x = x - bullet.hitBox.width / 2;
	bullet.hitBox.y = y;
	bullet.speed = 100.0f;
	
	if (bulletTexture.id == 0)
	{
		bulletTexture = LoadTexture("res/Bullet.png");
		bulletSound = LoadSound("res/Laser_Shoot.wav");
	}
	bullet.texture.texture = bulletTexture;
	bullet.texture.source.x = 0;
	bullet.texture.source.y = 0;
	bullet.texture.source.width = static_cast<float>(bullet.texture.texture.width);
	bullet.texture.source.height = static_cast<float>(bullet.texture.texture.height);
	bullet.texture.dest.width = static_cast<float>(bullet.hitBox.width);
	bullet.texture.dest.height = static_cast<float>(bullet.hitBox.height);
	bullet.texture.dest.x = bullet.hitBox.x;
	bullet.texture.dest.y = bullet.hitBox.y;
	PlaySound(bulletSound);
	return bullet;
}

void Entity::unloadBullet()
{
	UnloadTexture(bulletTexture);
	UnloadSound(bulletSound);
}
