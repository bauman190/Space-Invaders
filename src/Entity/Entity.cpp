#include "Entity.h"


Entity::Entity(Rectangle hitBox)
{
	this->hitBox = hitBox;
}

Entity::~Entity()
{

}
Rectangle Entity::getHitBox()
{
	return hitBox;
}