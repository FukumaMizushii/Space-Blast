#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height;
    lastFireTime = 0.0;
    lasersound = LoadSound("audio/laser_gun.wav");
}
Spaceship::~Spaceship() {
    UnloadTexture(image);
    UnloadSound(lasersound);
}
void Spaceship::Draw() {
    DrawTextureV(image, position, WHITE);
}


void Spaceship::MoveLeft(){

    position.x -= 6 ; 
    if( position.x < 0  ){
        position.x = 0 ; 
    }
}
 
 void Spaceship::MoveRight(){
    position.x += 6 ; 
    if( position.x > GetScreenWidth() - image.width){
        position.x = GetScreenWidth() - image.width; 
    }
 }
 void Spaceship::MoveUp(){
   position.y -= 6 ; 
   if(position.y - image.height < 0) {
    position.y = 0 ; 
   }

 }
  void Spaceship::MoveDown(){
   position.y += 6 ; 
   if( position.y > GetScreenHeight() - image.height) {
      position.y =  GetScreenHeight() - image.height;
   }
 }

 void Spaceship::FireLaser()
{
    if(GetTime() - lastFireTime >= 0.5) {
        lasers.push_back(Laser({position.x+ image.width / 2  - 2 , position.y}, -6));
        lastFireTime = GetTime();
        PlaySound(lasersound);
    }
 }

 Rectangle Spaceship::getRect()
 {
    return {position.x, position.y, float(image.width), float(image.height)};
 }

 void Spaceship::Reset()
 {
    position.x = (GetScreenWidth() - image.width) / 2.0f;
    position.y = GetScreenHeight() - image.height;
    lasers.clear();
 }
