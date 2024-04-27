#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>

class Entity {
    public:
        Entity(int x, int y);
        float entityX;
        float entityY;
        int height;
        int width;
        int direction;
        void move(std::pair<int,int> coords);
        void move(std::pair<int,int> coords, std::vector<int> map);
};