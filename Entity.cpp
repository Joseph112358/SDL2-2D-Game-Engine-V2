#include "Entity.h"
#include "Player.h"
#include <cmath>

Entity::Entity(){
    this->entityX = 1.0;
    this->entityY = 1.0;
    this->direction = 1;
}

// Maybe add a list of points to visit

// Maybe cache the route somehow?
void Entity::move(std::pair<int,int> coords){


    float xToMove = coords.first - entityX;
    float yToMove = coords.second - entityY;

    // Round the values
    xToMove = ((int)(xToMove * 100 + .5) / 100.0);
    yToMove = ((int)(yToMove * 100 + .5) / 100.0);

    float dist = sqrt((xToMove*xToMove)+(yToMove*yToMove));
    // Move x
    if(fabs(xToMove) > 0.3 && dist > 1){
        if(xToMove > 0){
            entityX += 0.1;
        }
        else {
            entityX -= 0.1;
        }
        entityX = ((int)(entityX * 100 + .5) / 100.0);
    }
    // Move y
    if(fabs(yToMove) > 0.3 && dist > 1){
           if(yToMove > 0){
            entityY += 0.1;
        }
        else {
            entityY -= 0.1;
        }
        entityY = ((int)(entityY * 100 + .5) / 100.0);
    }    


}