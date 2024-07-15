#include "Player.h"
#include "Level.h"
#include "cmath"


// Plan to move this over to Entity eventually
Player::Player(){
    this->playerX = 64;
    this->playerY = 64;
    this->direction = 0;
    this->playerIdle = true;
}

void Player::handlePlayerMovement(int direction, Level * level){
    // Change direction
    this->direction = direction;
        switch(direction){
            case 0:
            if(!checkWalkCollision(playerX,playerY-16, level)) {this->playerY -= 16;}
            break;
          case 90:
              if(!checkWalkCollision(playerX + 64, playerY, level)) {this->playerX += 16;}
            break;
          case 180:
            if(!checkWalkCollision(playerX,playerY+64, level)) {this->playerY += 16;}
            break;
          case 270:
            if(!checkWalkCollision(playerX -16, playerY, level)) {this->playerX -= 16;}
            break;
    }
}

bool Player::checkWalkCollision(int x , int y, Level * level){
    
    bool collisionOccured = false;
    int coordsToCheck = (y / 64) * level->mapX + (x/64);
    if(level->wallMap.at(coordsToCheck) == 1){
        collisionOccured = true;
    }
    return collisionOccured;
}

std::vector<int> Player::getNeighborTiles(std::vector<int> map, int mapX){
    std::vector<int> res;
    int playerPos = (playerY/64)*mapX + (playerX/64);
    res.push_back(playerPos - 1);
    res.push_back(playerPos + 1);
    res.push_back(playerPos + mapX);
    res.push_back(playerPos - mapX);
    return res;
}
