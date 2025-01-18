#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>
#include "SpriteFactory.h"
#include "../Sprite.h"
#include "../Level.h"
#include <queue>


class Entity {
    public:
        Entity(SDL_Rect rect, std::string id, Sprite * sprite);

        Entity(SDL_Rect rect, int direction, std::string id, Sprite * sprite);
        ~Entity() {
        }
        std::string id;
        SDL_Rect rect;        
        int direction;
        int speed;
        Sprite * sprite;

        // To be optimised
        bool moving;


        void update(Level * level);

        void getSpriteTransform(SDL_RendererFlip& flip, double& rotation);

        // New function for fireball, will be generic eventually
        bool isCollidingWithMap(Level * level);
};