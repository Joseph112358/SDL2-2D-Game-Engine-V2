#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>

// Plan to move this over to Entity eventually
class Player {
    public:
        Player();
        int playerX;
        int playerY;
        int direction;
        bool playerIdle;
        std::vector<int>  getNeighborTiles(std::vector<int> map, int mapX);
};