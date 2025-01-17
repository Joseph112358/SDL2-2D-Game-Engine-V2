#include "Player.h"
#include "Level.h"
#include "animations/Animations.h"
#include "cmath"

// Plan to move this over to Entity eventually
Player::Player(){
    this->playerX = 64;
    this->playerY = 64;
    this->direction = 0;
    this->speed = 8;
    this->playerIdle = true;
    this->animations = Animations();
}

// PlayerX % speed?

void Player::handlePlayerMovement(int direction, Level * level){
    // Change direction
    this->direction = direction;
        switch(direction){
            case 0:
              if(!checkWalkCollision(playerX,playerY-speed, level)) {this->playerY -= speed;}
              else if(playerY % speed > 0){
                playerY -= playerY % speed;
              }
            break;
          case 90:
              if(!checkWalkCollision(playerX + speed, playerY, level))
               {this->playerX += speed;}
               else if(playerX % speed > 0){
                playerX += playerX % speed;
               }
            break;
          case 180:
            if(!checkWalkCollision(playerX,playerY+speed, level)) {this->playerY += speed;}
            else if(playerY % speed > 0){
              playerY += playerY % speed;
            }
            break;
          case 270:
            if(!checkWalkCollision(playerX -speed, playerY, level)) {this->playerX -= speed;}
            else if(playerX % speed > 0){
                playerX -= playerX % speed;
               }
            break;
    }
}


// This needs to be rewritten to account for dynamic speed?
bool Player::checkWalkCollision(int x , int y, Level * level){

    // Check 4 points (x, y-32) (x, y-62) (x+64, y-32)    (x+64, y -64)
    bool isColliding = false;
    int XMin = x / 64;
    int XMax = (x+63) / 64;
    // int XMin = (x+16) / 64;
    // int XMax = (x+47) / 64;
    //int XMax = (x+48) / 64;
    int YMin = (y +32) / 64;
    int YMax = (y + 63) / 64;
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
