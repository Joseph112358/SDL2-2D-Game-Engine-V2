#include "Entity.h"

Entity::Entity(){
    this->entityX = 1.0;
    this->entityY = 1.0;
    this->direction = 1;
}

void Entity::move(){
    if(entityX == 2) direction = 1;
    if(entityX == 10) direction = -1;

    entityX += direction*1; // tile size
}