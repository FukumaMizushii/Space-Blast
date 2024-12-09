#pragma once
#include <raylib.h>

class Enemy {
    public:
        Enemy(int type, Vector2 position);
        void Draw();
        int GetType();
        static void UnloadImages();
        Rectangle getRect();
        static Texture2D enemyImages[3]; 
        Texture2D image;
        int type;
        bool act;
        Vector2 position;
};