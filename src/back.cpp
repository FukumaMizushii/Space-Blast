#include "back.hpp"

Back::Back()
{
    Load_image = LoadImageAnim("Graphics/6.gif", &animFrames);
    Backimage = LoadTextureFromImage(Load_image);
}

Back::~Back()
{
    UnloadTexture(Backimage);
}

void Back::Backdraw() {
    frameCounter++;
        if (frameCounter >= frameDelay)
        {
            currentAnimFrame++;
            if (currentAnimFrame >= animFrames) currentAnimFrame = 0;
            nextFrameDataOffset = Load_image.width*Load_image.height*4*currentAnimFrame;
            UpdateTexture(Backimage, ((unsigned char *)Load_image.data) + nextFrameDataOffset);

            frameCounter = 0;
        }
    DrawTexture(Backimage,40,0, WHITE);
}