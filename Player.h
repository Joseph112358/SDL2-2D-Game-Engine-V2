#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>
class Player {
    public:
        Player();
        float playerX;
        float playerY;
        int direction;
        bool playerIdle;
};