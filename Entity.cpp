#include "Entity.h"
#include <cmath>

Entity::Entity(int x, int y){
    this->entityX =  x;
    this->entityY =  y;
    this->direction = 1;
}

// Maybe add a list of points to visit?

// Maybe cache the route somehow?
void Entity::move(std::pair<int,int> coords){

    float xToMove = coords.first - entityX;
    float yToMove = coords.second - entityY;

    // Round the values
    xToMove = ((int)(xToMove * 100 + .5) / 100.0);
    yToMove = ((int)(yToMove * 100 + .5) / 100.0);

    float dist = sqrt((xToMove*xToMove)+(yToMove*yToMove));
    // Move x
    if(fabs(xToMove) > 0.1 && dist > 1){
        if(xToMove > 0){
            entityX += 0.1;
        }
        else {
            entityX -= 0.1;
        }
        entityX = ((int)(entityX * 100 + .5) / 100.0);
        // std::cout << dist << std::endl;
    }
    // Move y
    if(fabs(yToMove) > 0.1 && dist > 1){
           if(yToMove > 0){
            entityY += 0.1;
        }
        else {
            entityY -= 0.1;
        }
        entityY = ((int)(entityY * 100 + .5) / 100.0);
    }    
}

void Entity::move(std::pair<int,int> coords, std::vector<int> adjacentTiles){
    int mapX = 17;
    int EntityArrayPos = (int) entityX + entityY*mapX;
    int nearestTile = adjacentTiles.at(0);
    for( int tile : adjacentTiles){
        int currentTileDist = abs(EntityArrayPos - tile);
        nearestTile = std::min(nearestTile, tile);
    }
    // int currentX = (int) entityX;
    // int currentY = (int) entityY;
    std::cout << nearestTile << std::endl;
    // Work out routes
}
