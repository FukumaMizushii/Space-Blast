#pragma once
#include "spaceship.hpp"
#include "enemy.hpp"
#include "back.hpp"


class Game {
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        void DeleteInactiveLasers();
        void DeleteInactiveEnemies();
        void CheckForColl();
        void GameOver();
        void Reset();
        void InitGame();
        void MoveDownEnemies(double distance);
        void EnemyShootLaser();
        bool run;
        int lives;
        int score;
        float enemyLaserShootInterval;
        float timeLastEnemyFired;
        float TC;
        int enemiesDirection ; 
        Music music;
        Sound explode;
        Back back;
        Spaceship spaceship;
        std::vector<Enemy> enemies;
        std::vector<Laser> enemyLasers;
};