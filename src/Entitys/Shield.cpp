#include "Shield.h"


void Entity::inItShield(Shield& shield, int x ,int y)
{
	shield.hitbox.x = x;
	shield.hitbox.y = y;
	shield.hitbox.width = GetScreenWidth() * 0.05;
	shield.hitbox.height = shield.hitbox.width;
	shield.hp = 3;
	shield.color = BLUE;
}

void Entity::takeDamage(Shield& shield)
{
	shield.hp--;

	switch (shield.hp)
	{
	case 2:
		shield.color = YELLOW;
		break;
	case 1:
		shield.color = RED;
		break;
	default:
		shield.color = BLUE;
		break;
	}
}

void Entity::drawShield(Shield shield)
{
#ifdef _DEBUG 
	DrawRectangle(static_cast<int>(shield.hitbox.x), static_cast<int>(shield.hitbox.y), static_cast<int>(shield.hitbox.width), static_cast<int>(shield.hitbox.height), GREEN);
#endif 
	DrawCircle(shield.hitbox.x + shield.hitbox.width / 2, shield.hitbox.y + shield.hitbox.height / 2, shield.hitbox.width / 2, shield.color);
}