#include "Player.h"
#include "raylib.h"
#include "Bullet.h"
#include "vector"

extern int screenWidth;
extern int screenHeight;
extern std::vector<Entity::Bullet> bullets;

static void moveRight(Entity::Player& player)
{
	player.hitBox.x += player.speed * GetFrameTime();
}

static void moveLeft(Entity::Player& player)
{
	player.hitBox.x -= player.speed * GetFrameTime();
}

static void shoot(Entity::Player player)
{
	float x = player.hitBox.x + player.hitBox.width / 2;
	float y = player.hitBox.y;
	bullets.push_back(Entity::initBullet(x, y));
}

void Entity::drawPlayer(Player player)
{
	DrawRectangle(static_cast<int>(player.hitBox.x), static_cast<int>(player.hitBox.y), static_cast<int>(player.hitBox.width), static_cast<int>(player.hitBox.height), BLUE);
}

void Entity::updatePlayer(Player& player)
{
	if (IsKeyDown(KEY_D) && player.hitBox.x + player.hitBox.width < screenWidth)
	{
		moveRight(player);
	}
	if (IsKeyDown(KEY_A) && player.hitBox.x > 0)
	{
		moveLeft(player);
	}
	if (IsKeyPressed(KEY_SPACE))
	{
		shoot(player);
	}
}

void Entity::initPlayer(Player& player)
{
	float width = screenWidth * 0.05;
	float height = width;
	float x = static_cast<float>(screenWidth / 2 - width / 2);
	float y = static_cast<float>(screenHeight * 0.90);
	player.hitBox = { x, y, width, height };
	player.maxHP = 3;
	player.HP = player.maxHP;
	player.score = 0;
	player.speed = 300.0f;

}
