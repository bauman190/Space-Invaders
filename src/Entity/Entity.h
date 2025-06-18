#pragma once
#include "raylib.h"

namespace Entity
{
	class Entity
	{
	protected:
		Rectangle hitBox;

	public:
		Entity(Rectangle hitBox);
		virtual ~Entity();
		virtual void draw() = 0;
		Rectangle getHitBox();

	};
}

