#include "Player.h"

#include "raylib.h"

#include "Bullet.h"
#include "Game/gameManager.h"

extern GM::gameManager gamemanager;

static Texture playerTexture;


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
	gamemanager.bullets.push_back(Entity::initBullet(x, y));
}

void Entity::drawPlayer(Player player)
{

#ifdef _DEBUG 
	DrawRectangle(static_cast<int>(player.hitBox.x), static_cast<int>(player.hitBox.y), static_cast<int>(player.hitBox.width), static_cast<int>(player.hitBox.height), BLUE);
#endif 

	const float rotation = -90.0f;

	DrawTexturePro(player.texture.texture,
		player.texture.source,
		player.texture.dest,
		{ player.texture.dest.width / 2.0f, player.texture.dest.height / 2.0f },
		rotation,
		WHITE);
}

void Entity::updatePlayer(Player& player)
{
	if (IsKeyDown(KEY_D) && player.hitBox.x + player.hitBox.width < gamemanager.screenWidth)
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
	player.texture.dest.x = player.hitBox.x + player.hitBox.width / 2;
	player.texture.dest.y = player.hitBox.y + player.hitBox.height / 2;
}

void Entity::initPlayer(Player& player)
{
	Entity::restarPlayer(player);
	playerTexture = LoadTexture("res/Nave1.png");
	player.texture.texture = playerTexture;
	player.texture.source.x = 0;
	player.texture.source.y = 0;
	player.texture.source.width = static_cast<float>(player.texture.texture.width);
	player.texture.source.height = static_cast<float>(player.texture.texture.height);
	player.texture.dest.width = static_cast<float>(player.hitBox.width);
	player.texture.dest.height = static_cast<float>(player.hitBox.height);
	player.texture.dest.x = player.hitBox.x;
	player.texture.dest.y = player.hitBox.y;

}

void Entity::increasScore(Player& player)
{
	player.score++;
}

void Entity::unloadPlayerTexture()
{
	UnloadTexture(playerTexture);
}

void Entity::restarPlayer(Player& player)
{
	float width = gamemanager.screenWidth * 0.05;
	float height = width;
	float x = static_cast<float>(gamemanager.screenWidth / 2 - width / 2);
	float y = static_cast<float>(gamemanager.screenHeight * 0.90);
	player.hitBox = { x, y, width, height };
	player.maxHP = 3;
	player.HP = player.maxHP;
	player.score = 0;
	player.speed = 300.0f;
}