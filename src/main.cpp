#include <raylib.h>
#include "game.hpp"
#include <string>
#include <iostream>

int main()
{
    int windowWidth = 800;
    int windowHeight = 720;

    InitWindow(windowWidth, windowHeight, "Space Blast");
    InitAudioDevice();
    SetTargetFPS(60); 

    Font font = LoadFontEx("Font/GAMEOVER.ttf",64,0,0);
    Font font2 = LoadFontEx("Font/PlayWithFire.ttf",64,0,0); 
    Font font3 = LoadFontEx("Font/LoSpaccone.otf",64,0,0);
    Font font4 = LoadFontEx("Font/KAISG.ttf",64,0,0);

    Texture2D spaceshipImage = LoadTexture("Graphics/HP.png");

    Game game;
    Back back;
  
    while(WindowShouldClose() == false) { 

        BeginDrawing();
        ClearBackground(BLACK);

        game.HandleInput();
        game.Update(); 

        std::string  TextString = std::to_string(game.score);
        std::string FinalScore = "Your Score :  " + TextString;

        back.Backdraw();
        
        if(!game.run) {
            ClearBackground(BLACK);

            DrawTextEx(font2, "SpAcE bLaST", {120, 50}, 74, 2, SKYBLUE);
            DrawTextEx(font3, "Oppss...!! GAME OVER", {70, 230}, 72, 2, RED);
            DrawTextEx(font3, FinalScore.c_str(), {75, 307}, 45, 2, BLUE);
            DrawTextEx(font, "\"PreSs  Enter  to  Revive\"", {140, 400}, 27, 2, YELLOW);
            DrawTextEx(font4, "Moshiour", {580, 600}, 50, 2, GOLD);
            DrawTextEx(font4, "Monikumar", {560, 660}, 50, 2, GOLD);
        }
        
        if(game.run) {
            float x = 750.0 ; 
            for(int i = 0 ; i < game.lives ; i++){
            DrawTextureV(spaceshipImage , {x , 0}, WHITE); 
            x -= 50 ; 
            }
            
            game.Draw();    

            // std::cout << game.enemyLasers.size() << '\n';
            std::cout << game.enemies.size() << '\n';
            UpdateMusicStream(game.music);
            DrawTextEx(font3, "SCORE", {10, 10}, 25, 2, YELLOW);
            int NumZero = 5 - TextString.size();
            TextString = std::string(NumZero, '0') + TextString;
            DrawTextEx(font3, TextString.c_str(), {10, 30}, 28, 2, YELLOW);
        }


        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
}