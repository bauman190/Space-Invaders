#include "Entity.h"


Entity::Entity::Entity(Rectangle hitBox)
{
	this->hitBox = hitBox;
}

Entity::Entity::~Entity()
{

}
Rectangle Entity::Entity::getHitBox()
{
	return hitBox;
}