#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>
#include "Level.h"
#include "animations/Animations.h"

// Plan to move this over to Entity eventually
class Player {
    public:
        Player();
        int playerX;
        int playerY;
        int speed;
        int direction;
        bool playerIdle;
        Animations animations;
        void handlePlayerMovement(int direction, Level * level);
        void movePlayer(int dx, int dy, Level* level);
        bool checkWalkCollision(int x, int y, Level * level);
        std::vector<int>  getNeighborTiles(std::vector<int> map, int mapX);
};