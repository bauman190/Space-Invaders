#include "Player.h"

Player::Player(Rectangle hitBox, int maxHP, float speed) : Entity (hitBox)
{
	this->maxHP = maxHP;
	HP = maxHP;
	this->speed = speed;
	score = 0;
}
void Player::moveRight()
{
	hitBox.x += speed * GetFrameTime();
}
void Player::moveLeft()
{
	hitBox.x -= speed * GetFrameTime();
}
void Player::draw()
{
	DrawRectangle(static_cast<int>(hitBox.x), static_cast<int>(hitBox.y), static_cast<int>(hitBox.width), static_cast<int>(hitBox.height), BLUE);
}
Player::~Player()
{

}