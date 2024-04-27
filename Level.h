#pragma once
#include <vector>
#include "Entity.h"
class Level {
    public:
        Level(int mapX, int mapY, std::vector<int> floorMap, std::vector<int> wallMap);
        Level();
        // Abstract to some kind of map class?
        int mapX;
        int mapY;
        std::vector<int> floorMap;
        std::vector<int> wallMap;
        std::vector<int> itemMap;
        std::vector<Entity> entites;
        int getMapX();
        bool inMap(int x, int y);
};