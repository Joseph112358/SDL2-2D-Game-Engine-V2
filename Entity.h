#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>
#include <queue>


class Entity {
    public:
        Entity(int x, int y);
        int entityX;
        int entityY;
        int height;
        int width;
        int direction;


        // To be optimised
        bool moving;
        std::pair<int, int> currentDestination;
        std::queue<std::pair<int,int>> moveQueue;
        void moveToGivenPoint(std::pair<int,int> coords, std::vector<int> map);
};