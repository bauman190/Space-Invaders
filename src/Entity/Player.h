#pragma once
#include "Entity.h"
#include "raylib.h"


class Player : public Entity
{
private:
	int score;
	int HP;
	int maxHP;
	float speed;

public:
	Player(Rectangle hitBox, int maxHP, float speed);
	~Player();
	void moveRight();
	void moveLeft();
	void draw() override;


};

