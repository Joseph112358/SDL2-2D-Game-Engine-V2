#include "Player.h"
#include "cmath"


// Plan to move this over to Entity eventually
Player::Player(){
    this->playerX = 64;
    this->playerY = 64;
    this->direction = 0;
    this->playerIdle = true;
}

std::vector<int> Player::getNeighborTiles(std::vector<int> map, int mapX){
    std::vector<int> res;
    int playerPos = (int)(floorf(playerY)*mapX + floorf(playerX));
    res.push_back(playerPos - 1);
    res.push_back(playerPos + 1);
    res.push_back(playerPos + mapX);
    res.push_back(playerPos - mapX);
    return res;
}
