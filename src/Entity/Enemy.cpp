#include "Enemy.h"


Entity::Enemy::Enemy(Rectangle hitBox, float speed) : Entity(hitBox)
{
	this->speed = speed;
}
void Entity::Enemy::movement()
{
	hitBox.x += speed * GetFrameTime();
}
void Entity::Enemy::draw()
{
	DrawRectangle(static_cast<int>(hitBox.x), static_cast<int>(hitBox.y), static_cast<int>(hitBox.width), static_cast<int>(hitBox.height), RED);
}
Entity::Enemy::~Enemy()
{

}