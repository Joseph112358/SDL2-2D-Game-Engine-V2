#pragma once
#include <vector>
#include <map>
#include <memory>
#include "./game_objects/IInteractable.hpp"
class Level {
    public:
        Level(int mapX, int mapY, std::vector<int> floorMap, std::vector<int> wallMap);
        Level(int levelCode);
        // Abstract to some kind of map class?
        int mapX;
        int mapY;
        std::vector<int> floorMap;
        std::vector<int> wallMap;
        // std::vector<int> itemMap;
        std::map<int, std::unique_ptr<IInteractable>> interactables;
        int getMapX();
        bool inMap(int x, int y);
};