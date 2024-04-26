#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>
#include "Player.h"
class Entity {
    public:
        Entity();
        float entityX;
        float entityY;
        int direction;
        void move(std::pair<int,int> coords);
};