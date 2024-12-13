#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>
#include "SpriteFactory.h"
#include "../Sprite.h"
#include <queue>


class Entity {
    public:
        Entity(int x, int y, std::string id, Sprite * sprite);
        ~Entity() {
        }
        std::string id;
        int entityX;
        int entityY;
        int height;
        int width;
        int direction;
        Sprite * sprite;


        // To be optimised
        bool moving;
        void update();
        std::pair<int, int> currentDestination;
        std::queue<std::pair<int,int>> moveQueue;
        void moveToGivenPoint(std::pair<int,int> coords, std::vector<int> map);
};