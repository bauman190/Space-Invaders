#include "raylib.h"
#include "Game.h"
#include "Entity/Player.h"
#include "Entity/Enemy.h"
#include "vector"

const int screenWidth = 800;
const int screenHeight = 450;


static void draw(Entity::Player player, std::vector<Entity::Entity*> enemy);

void input(Entity::Player& player);

void game::runGame()
{
    InitWindow(screenWidth, screenHeight, "Space Invaders");

    Rectangle hitBox = { screenWidth / 2, screenHeight * 0.90, 20, 20 };

    Entity::Player player = Entity::Player(hitBox, 10, 300);

    hitBox = { screenWidth * 0.2, screenHeight * 0.10, 20, 20 };

    std::vector<Entity::Entity*> entitys;

    entitys.push_back(new Entity::Enemy(hitBox, 100));

    float initialX = hitBox.x;

    for (size_t j = 0; j < 5; j++)
    {
        hitBox.x = initialX;
        if (j >= 1)
        {
            hitBox.y += hitBox.height + 10;
        }

        entitys.push_back(new Entity::Enemy(hitBox, 100));

        for (int i = 1; i < 15; i++)
        {
            hitBox.x += entitys[i - 1]->getHitBox().width + 10;
            entitys.push_back(new Entity::Enemy(hitBox, 100));
        }
    }
    while (!WindowShouldClose())
    {
        input(player);

        for (size_t i = 0; i < entitys.size(); i++)
        {
            Entity::Enemy* enemy = dynamic_cast<Entity::Enemy*>(entitys[i]);
            if (enemy)
            {
               enemy->movement();
            }
            
        }
        

        draw(player, entitys);
    }

    for (size_t i = 0; i < entitys.size(); i++)
    {
        delete entitys[i];
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


static void draw(Entity::Player player, std::vector<Entity::Entity*> entitys)
{
    BeginDrawing();

    ClearBackground(BLACK);

    player.draw();


    for (size_t i = 0; i < entitys.size(); i++)
    {
        entitys[i]->draw();
    }
   
    EndDrawing();
}

