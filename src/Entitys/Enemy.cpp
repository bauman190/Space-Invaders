#include "Enemy.h"

extern int screenWidth;
extern int screenHeight;


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
	float width = screenWidth * 0.05;
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