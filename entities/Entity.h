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

        Entity(int x, int y,int direction, std::string id, Sprite * sprite);
        ~Entity() {
        }
        std::string id;
        int entityX;
        int entityY;
        int height;
        int width;
        int direction;
        int speed;
        Sprite * sprite;


        // To be optimised
        bool moving;


        void update(const std::vector<int>& map);

        void getSpriteTransform(SDL_RendererFlip& flip, double& rotation);

        // New function for fireball, will be generic eventually
        bool isCollidingWithMap(const std::vector<int>& map);
        std::pair<int, int> currentDestination;
        std::queue<std::pair<int,int>> moveQueue;
        void moveToGivenPoint(std::pair<int,int> coords, std::vector<int> map);
};