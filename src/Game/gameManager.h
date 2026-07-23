#pragma once

#include "Entitys/Bullet.h"
#include "Entitys/Player.h"
#include "Entitys/Enemy.h"
#include "Scenes/screen_options.h"
#include <vector>

namespace GM
{

struct gameManager
{
	Entity::Player player;
	std::vector <Entity::Enemy> enemys;
	std::vector <Entity::Bullet> bullets;
	std::vector <Entity::Bullet> enemysBullets;

	scenes::Screen currentScreen = scenes::MainMenu;
	int screenWidth = 800;
	int screenHeight = 600;

	float enemyWallCooldown = 0.0f;
	float enemyShootTimer = 0.0f;

	bool gamePaused;
	bool exitGame;

	Music music;
};
}