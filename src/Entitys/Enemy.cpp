#include "Enemy.h"

#include "raylib.h"

#include "vector"
#include "Bullet.h"
#include "Game/gameManager.h"

extern GM::gameManager gamemanager;

static Texture alienTexture; 

void Entity::drawEnemy(Enemy enemy)
{
#ifdef _DEBUG 
	DrawRectangle(static_cast<int>(enemy.hitBox.x), static_cast<int>(enemy.hitBox.y), static_cast<int>(enemy.hitBox.width), static_cast<int>(enemy.hitBox.height), RED);
#endif
	DrawTexturePro(enemy.texture.texture ,enemy.texture.source,enemy.texture.dest ,{0, 0}, 0, WHITE);
}
void Entity::updateEnemy(Enemy& enemy)
{
	enemy.hitBox.x += enemy.speed * GetFrameTime();
	enemy.texture.dest.x = enemy.hitBox.x;
	enemy.texture.dest.y = enemy.hitBox.y;
}
void Entity::initEnemy(Enemy& enemy, float x, float y)
{
	Entity::createEnemy(enemy, x, y);

	if (alienTexture.id == 0)
	{
		alienTexture = LoadTexture("res/Alien.png");
	}
	enemy.texture.texture = alienTexture;
	enemy.texture.source.x = 0;
	enemy.texture.source.y = 0;
	enemy.texture.source.width = static_cast<float>(enemy.texture.texture.width);
	enemy.texture.source.height = static_cast<float>(enemy.texture.texture.height);
	enemy.texture.dest.width = static_cast<float>(enemy.hitBox.width);
	enemy.texture.dest.height = static_cast<float>(enemy.hitBox.height);
	enemy.texture.dest.x = enemy.hitBox.x;
	enemy.texture.dest.y = enemy.hitBox.y;
}

void Entity::enemyChangeDir(Enemy& enemy)
{
	enemy.speed *= -1.0f;
}

void Entity::enemyGoDown(Enemy& enemy)
{
	enemy.hitBox.y += enemy.hitBox.height;
}

void Entity::enemyShoot(Enemy enemy)
{
	float x = enemy.hitBox.x + enemy.hitBox.width / 2;
	float y = enemy.hitBox.y + enemy.hitBox.height;
	Entity::Bullet newBullet = Entity::initBullet(x, y);
	newBullet.speed *= -1.0f;
	gamemanager.enemysBullets.push_back(newBullet);
}

void Entity::unloadEnemyTexture()
{
	UnloadTexture(alienTexture);
}

void Entity::createEnemy(Enemy& enemy, float x, float y)
{
	float width = gamemanager.screenWidth * 0.06;
	float height = width;
	enemy.hitBox = { x, y, width, height };
	enemy.speed = 50.0f;
}