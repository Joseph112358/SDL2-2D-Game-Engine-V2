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

void Player::handlePlayerMovement(int direction, Level* level) {
    // Change direction
    this->direction = direction;

    // Define movement deltas for each direction
    int dx = 0, dy = 0;
    switch (direction) {
        case 0:   dy = -speed; break; // Up
        case 90:  dx = speed;  break; // Right
        case 180: dy = speed;  break; // Down
        case 270: dx = -speed; break; // Left
        default: return; // Invalid direction, do nothing
    }

    // Attempt to move, adjusting position if collision occurs
    movePlayer(dx, dy, level);
}

void Player::movePlayer(int dx, int dy, Level* level) {
    int newPlayerX = playerX + dx;
    int newPlayerY = playerY + dy;

    if (!checkWalkCollision(newPlayerX, newPlayerY, level)) {
        // Update position if no collision
        playerX = newPlayerX;
        playerY = newPlayerY;
    } else {
        // Adjust position to align with the grid
        if (dx != 0 && playerX % speed != 0) {
            playerX += (dx > 0 ? speed - playerX % speed : -playerX % speed);
        }
        if (dy != 0 && playerY % speed != 0) {
            playerY += (dy > 0 ? speed - playerY % speed : -playerY % speed);
        }
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
