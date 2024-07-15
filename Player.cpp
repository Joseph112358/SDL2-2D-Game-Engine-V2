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
              if(!checkWalkCollision(playerX + 16, playerY, level)) {this->playerX += 16;}
            break;
          case 180:
            if(!checkWalkCollision(playerX,playerY+16, level)) {this->playerY += 16;}
            break;
          case 270:
            if(!checkWalkCollision(playerX -16, playerY, level)) {this->playerX -= 16;}
            break;
    }
}

bool Player::checkWalkCollision(int x , int y, Level * level){

    // Check 4 points (x, y-32) (x, y-62) (x+64, y-32)    (x+64, y -64)
    bool isColliding = false;
    int XMin = x / 64;
    int XMax = (x+48) / 64;
    int YMin = (y +32) / 64;
    int YMax = (y + 48) / 64;
    if(level->wallMap.at(YMin*level->mapX+XMin) == 1){isColliding = true;}
    if(level->wallMap.at(YMin*level->mapX+XMax) == 1){isColliding = true;}
    if(level->wallMap.at(YMax*level->mapX+XMin) == 1){isColliding = true;}
    if(level->wallMap.at(YMax*level->mapX+XMax) == 1){isColliding = true;}

    return isColliding;
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
