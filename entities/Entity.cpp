#include "Entity.h"
#include "../Sprite.h"
#include <cmath>

int entityMoveSpeed = 4;
Entity::Entity(int x, int y, std::string id, Sprite * sprite){
    this->id = id;
    this->entityX =  x;
    this->entityY =  y;
    this->direction = 1;
    this->moving = false;
    this->sprite = sprite;
}

// Maybe add a list of points to visit / process?

// Have components instead e.g. for entity, apply compenent effect (movement etc) if valid (e.g. in motion)

// Check for collisions
//   if yes, explode -> whatever this should be
//   if no move forward
void Entity::update(const std::vector<int>& map){
    if(this->id == "fireball"){
        bool colliding = isCollidingWithMap(map);
        // Check for collisions
        // Pass coords and height + width
        if(!colliding){
            this->entityX = this->entityX += 4;
        }
        // this->entityX = this->entityX += 4;
    }
}

bool Entity::isCollidingWithMap(const std::vector<int>& map){

    // Calculate place on map
    // PASS IN LEVEL INSTEAD FOR MAPX (or width) use 17 for now

    // int xRounded = entityX / 64;
    //  q = (x + y - 1) / y;
    int xRounded = (entityX  + 63) / 64;
    int yRounded = entityY / 64;

    int levelMapIndex = (yRounded * 17) + xRounded;
    // SDL_Log("thing: %d" , levelMapIndex);

    if(map[levelMapIndex] == 0){
        SDL_Log("Thing: %d", xRounded);
        return false;
    }
    return true;
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
