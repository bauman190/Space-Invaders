#include "Enemy.h"
#include "vector"
#include "Bullet.h"

extern int screenWidth;
extern int screenHeight;
extern std::vector<Entity::Bullet> enemysBullets;

void Entity::drawEnemy(Enemy enemy)
{
	DrawRectangle(static_cast<int>(enemy.hitBox.x), static_cast<int>(enemy.hitBox.y), static_cast<int>(enemy.hitBox.width), static_cast<int>(enemy.hitBox.height), RED);
}
void Entity::updateEnemy(Enemy& enemy)
{
	enemy.hitBox.x += enemy.speed * GetFrameTime();
}
void Entity::initEnemy(Enemy& enemy, float x, float y)
{
	float width = screenWidth * 0.03;
	float height = width;
	enemy.hitBox = { x, y, width, height };
	enemy.speed = 50.0f;
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
	enemysBullets.push_back(newBullet);
}