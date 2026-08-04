#include "Shield.h"



void Entity::inItShield(Shield& shield, int x ,int y)
{
	shield.hitbox.x = x;
	shield.hitbox.y = y;
	shield.hitbox.width = GetScreenWidth() * 0.05;
	shield.hitbox.height = shield.hitbox.width;
	shield.hp = 3;
	shield.texture = LoadTexture("res/Shield .png");

	float frameWidth = shield.texture.width / 3.0f;

	shield.sourceRec = {
		0,
		0,
		frameWidth,
		static_cast<float>(shield.texture.height)
	};
}

void Entity::takeDamage(Shield& shield)
{
	shield.hp--;

	float frameWidth = shield.texture.width / 3.0f;

	switch (shield.hp)
	{
	case 2:
		shield.sourceRec.x = frameWidth * 1;
		break;
	case 1:
		shield.sourceRec.x = frameWidth * 2;
		break;
	default:
		shield.sourceRec.x = frameWidth;
		break;
	}
}

void Entity::drawShield(Shield shield)
{
#ifdef _DEBUG 
	DrawRectangle(static_cast<int>(shield.hitbox.x), static_cast<int>(shield.hitbox.y), static_cast<int>(shield.hitbox.width), static_cast<int>(shield.hitbox.height), GREEN);
#endif 
	DrawTexturePro(shield.texture, shield.sourceRec, shield.hitbox, { 0, 0 }, 0.0f, WHITE);
}

void Entity::unloadShield(Shield& shield)
{
	UnloadTexture(shield.texture);
}