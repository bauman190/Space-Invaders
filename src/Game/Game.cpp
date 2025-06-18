#include "raylib.h"
#include "Game.h"
#include "Entity/Player.h"

const int screenWidth = 800;
const int screenHeight = 450;


static void draw(Player player);

void input(Player& player);

void game::runGame()
{
    InitWindow(screenWidth, screenHeight, "Space Invaders");

    Rectangle hitBox = { screenWidth / 2, screenHeight * 0.90, 20, 20 };

    Player player = Player(hitBox, 10, 100);

    while (!WindowShouldClose())
    {
        input(player);

        draw(player);
    }


    CloseWindow();
}

void input(Player& player)
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


static void draw(Player player)
{
    BeginDrawing();

    ClearBackground(BLACK);

    player.draw();

    EndDrawing();
}
