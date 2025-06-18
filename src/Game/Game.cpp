#include "raylib.h"
#include "Game.h"
#include "Entity/Player.h"

const int screenWidth = 800;
const int screenHeight = 450;


static void draw(Entity::Player player);

void input(Entity::Player& player);

void game::runGame()
{
    InitWindow(screenWidth, screenHeight, "Space Invaders");

    Rectangle hitBox = { screenWidth / 2, screenHeight * 0.90, 20, 20 };

    Entity::Player player = Entity::Player(hitBox, 10, 300);

    while (!WindowShouldClose())
    {
        input(player);

        draw(player);
    }


    CloseWindow();
}

void input(Entity::Player& player)
{
    if (IsKeyDown(KEY_A) && player.getHitBox().x > 0)
    {
        player.moveLeft();
    }
    if (IsKeyDown(KEY_D) && player.getHitBox().x + player.getHitBox().width < screenWidth)
    {
        player.moveRight();
    }
}


static void draw(Entity::Player player)
{
    BeginDrawing();

    ClearBackground(BLACK);

    player.draw();

    EndDrawing();
}
