#pragma once
#include <vector>
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
        int getMapX();
        bool inMap(int x, int y);
};