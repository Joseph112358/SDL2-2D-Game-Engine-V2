#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>
#include "Level.h"
#include "Animations.h"

// Plan to move this over to Entity eventually
class Player {
    public:
        Player();
        int playerX;
        int playerY;
        int direction;
        bool playerIdle;
        Animations animations;
        void handlePlayerMovement(int direction, Level * level);
        bool checkWalkCollision(int x, int y, Level * level);
        std::vector<int>  getNeighborTiles(std::vector<int> map, int mapX);
};