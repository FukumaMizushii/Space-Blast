#pragma once
#include <raylib.h>

class Back{
    public:
        Back();
        ~Back();
        void Backdraw();
    private:
    int animFrames;
    unsigned int nextFrameDataOffset = 0;
    int currentAnimFrame = 0;
    int frameDelay = 3;
    int frameCounter = 0;
    Image Load_image;
    Texture2D Backimage;
};