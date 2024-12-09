#include "game.hpp"
#include <iostream>

Game::Game()
{
    music = LoadMusicStream("audio/music.wav");
    explode = LoadSound("audio/explode.wav");
    PlayMusicStream(music);
    InitGame();
}

Game::~Game() {
    Enemy:: UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explode);
}

void Game::Update(){
    if(run) {
        for(auto& laser: spaceship.lasers){
            laser.Update();  
        }
        
        MoveDownEnemies(2);

        double CT = GetTime(); 
        enemyLaserShootInterval = enemies.size() > 3 ? 0.3 : 2;
        if( CT - timeLastEnemyFired>= enemyLaserShootInterval &&  !enemies .empty() ){
            int randomIndex = GetRandomValue(0, enemies.size() - 1);
            Enemy &enemy = enemies[randomIndex];
            if(enemy.type == 1) {
                enemyLasers.push_back(Laser({enemy.position.x + enemy.enemyImages[enemy.type - 1].width/2, enemy.position.y + enemy.enemyImages[enemy.type - 1].height}, 4));
            }
            else if(enemy.type == 2) {
                enemyLasers.push_back(Laser({enemy.position.x + enemy.enemyImages[enemy.type - 1].width/4.0f, enemy.position.y + enemy.enemyImages[enemy.type - 1].height}, 6));
                enemyLasers.push_back(Laser({enemy.position.x + 3*enemy.enemyImages[enemy.type - 1].width/4.0f, enemy.position.y + enemy.enemyImages[enemy.type - 1].height}, 6));
            }
            else if(enemy.type == 3) {
                enemyLasers.push_back(Laser({enemy.position.x + enemy.enemyImages[enemy.type - 1].width/6.0f, enemy.position.y + enemy.enemyImages[enemy.type - 1].height}, 8));
                enemyLasers.push_back(Laser({enemy.position.x + enemy.enemyImages[enemy.type - 1].width/2.0f, enemy.position.y + enemy.enemyImages[enemy.type - 1].height}, 10));
                enemyLasers.push_back(Laser({enemy.position.x + 5*enemy.enemyImages[enemy.type - 1].width/6.0f, enemy.position.y + enemy.enemyImages[enemy.type - 1].height}, 8));
            }
            timeLastEnemyFired = GetTime();
        } 
        DeleteInactiveLasers();
        DeleteInactiveEnemies();
        CheckForColl();

        for(auto &laser:enemyLasers) {
            laser.Update();
        }

        if(CT - TC >= 3.0 && TC < 24.0) {
            Vector2 random;
            random.x = GetRandomValue(60, 750);
            random.y = -50;
            enemies.push_back(Enemy(1, random));
            TC = GetTime();
        }
        if(CT - TC >= 1.5 && (TC > 18.0 && TC < 25.0)) {
            Vector2 random;
            random.x = GetRandomValue(60, 750);
            random.y = -50;
            enemies.push_back(Enemy(2, random));
            TC = GetTime();
        }
        if(CT - TC >= 1.0 && (TC > 25.0 && TC < 40.0)) {
            Vector2 random;
            random.x = GetRandomValue(60, 750);
            random.y = -50;
            enemies.push_back(Enemy(2, random));
            TC = GetTime();
        }
        if(CT - TC >= 0.8 && TC > 35.0) {
            Vector2 random;
            random.x = GetRandomValue(60, 750);
            random.y = -50;
            enemies.push_back(Enemy(3, random));
            TC = GetTime();
        }  

    }
}

void Game::Draw() {
    for(auto &laser:enemyLasers) {
        laser.Draw();
    }
    spaceship.Draw();


    for(auto& enemy: enemies) {
        enemy.Draw();
    }

    for(auto&laser: spaceship.lasers){
        laser.Draw(); 
    }
}

void::Game::HandleInput(){
    if(run) {
        if(IsKeyDown(KEY_LEFT)){
            spaceship.MoveLeft();
        }
        else if ( IsKeyDown(KEY_RIGHT)){
            spaceship.MoveRight(); 
        }
         else if ( IsKeyDown(KEY_UP)){
            spaceship.MoveUp();
        }
        else if ( IsKeyDown(KEY_DOWN)){
            spaceship.MoveDown();
        }
        else if ( (IsKeyDown(KEY_SPACE) && IsKeyDown(KEY_LEFT)) || (IsKeyDown(KEY_SPACE) )) {
            spaceship.FireLaser();
        }
    }
    else {
        if(IsKeyDown(KEY_ENTER)) {
            Reset();
            InitGame();
        }
    }
}

void Game::DeleteInactiveLasers() {
        for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
            if(!it -> active) {
                it = spaceship.lasers.erase(it);
            }
            else {
                ++it;
            }
        }
         for(auto it = enemyLasers.begin(); it != enemyLasers.end();) {
            if(!it -> active) {
                it = enemyLasers.erase(it);
            }
            else {
                ++it;
            }
        }
}

void Game::DeleteInactiveEnemies()
{
    for(auto it = enemies.begin();it != enemies.end();) {
        if(!it -> act) {
            it = enemies.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Game::CheckForColl()
{
    //for spaceship

    for(auto &laser: spaceship.lasers) {
        auto it = enemies.begin();
        while(it != enemies.end()) {
            if(CheckCollisionRecs(it -> getRect(), laser.getRect())) {
                if(it -> type == 1) {
                    score += 100;
                }
                else if(it -> type == 2) {
                    score += 200;
                }
                else if(it -> type == 3) {
                    score += 300;
                }
                PlaySound(explode);
                it = enemies.erase(it);
                laser.active = false;
            }
            else {
                ++it;
            }
        }
    }
    
    //for enemy
    for(auto &laser:enemyLasers) {
        if(CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
            laser.active = false;
            lives--;
            if(lives == 0 ) {
                GameOver();
            }
        }
    }

    for(auto &enemy: enemies) {
        if(CheckCollisionRecs(enemy.getRect(), spaceship.getRect())) {
            GameOver();
        }
    }
}

void Game::GameOver()
{
    run = false;
    enemies.clear();
    enemyLasers.clear();
}

void Game::Reset()
{
    spaceship.Reset();
    enemies.clear();
    enemyLasers.clear();
}

void Game::InitGame()
{
    TC = 0.0;
    timeLastEnemyFired = 0.0; 
    lives = 3;
    score = 0;
    run = true;
}

void Game::MoveDownEnemies(double distance) {
    for(auto& enemy: enemies) {
        enemy.position.y += distance;
        // if( enemy.position.y >=  GetScreenHeight()){
        //     GameOver();
        // }
        if (enemy.act){
            if(enemy.position.y > GetScreenHeight()){
                enemy.act = false; 
            }
    }
    }
}

