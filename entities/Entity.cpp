#include "Entity.h"
#include "../Sprite.h"
#include <cmath>

int entityMoveSpeed = 4;
Entity::Entity(int x, int y, Sprite * sprite){
    this->entityX =  x;
    this->entityY =  y;
    this->direction = 1;
    this->moving = false;
    this->sprite = sprite;
}

// Maybe add a list of points to visit / process?

void Entity::update(){
    // this->entityX = this->entityX += 2;
}

// Is map even needed?
void Entity::moveToGivenPoint(std::pair<int,int> coords, std::vector<int> map){
    int distX = std::abs(coords.first - entityX);
    int distY = std::abs(coords.second - entityY);

    // Move x
    if( distX != 0){
        if(entityX > coords.first){
            entityX -= entityMoveSpeed;
        } 
        else if(entityX < coords.first){
            entityX += entityMoveSpeed;
        }
    }
    // else move y
    else if(distY !=0){
        if(entityY > coords.second){
            entityY -= entityMoveSpeed;
        } 
        else if(entityY < coords.second){
            entityY += entityMoveSpeed;
        }
    }
    else{
        moving = false;
    }
}
