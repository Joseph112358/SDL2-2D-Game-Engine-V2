#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>
class Entity {
    public:
        Entity();
        float entityX;
        float entityY;
        int direction;
        void move();
};