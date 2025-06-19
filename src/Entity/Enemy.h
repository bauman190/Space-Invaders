#pragma once
#include "Entity.h"

namespace Entity
{
	class Enemy : public Entity
	{
	private:
		float speed;

	public:
		Enemy(Rectangle hitBox, float speed);
		~Enemy();
		void movement();
		void draw() override;
	};
}
