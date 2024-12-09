#include "enemy.hpp"
#include <iostream>

Texture2D Enemy::enemyImages[3] = {};

Enemy::Enemy(int type, Vector2 position)
{
    this -> type = type;
    this -> position = position;
    act = true;

    if(enemyImages[type - 1 ].id == 0 ){

    switch(type) {
        case 1 :
             enemyImages[0] = LoadTexture("Graphics/enemy1.png");
            break;
        case 2:
            enemyImages[1] = LoadTexture("Graphics/enemy2.png");
            break;
        case 3:
            enemyImages[2] = LoadTexture("Graphics/enemy3.png");
            break;
        default:
            enemyImages[0] = LoadTexture("Graphics/enemy1.png");
            break;
    }
  }
}

void Enemy::Draw() {
    DrawTextureV(enemyImages[type - 1 ], position, WHITE);
}

int Enemy::GetType() {
    return type;
}

void Enemy::UnloadImages()
{
    for( int i = 0 ; i < 4 ; i++){
        UnloadTexture(enemyImages[i]);
    }
}

Rectangle Enemy::getRect()
{
    return {position.x, position.y, float(enemyImages[type - 1].width), float(enemyImages[type - 1].height)};
}
