#include "Entity.h"
#include "../Sprite.h"
#include <cmath>

int entityMoveSpeed = 4;
Entity::Entity(int x, int y, std::string id, Sprite * sprite){
    this->id = id;
    this->entityX =  x;
    this->entityY =  y;
    this->direction = 90;
    this->moving = false;
    this->sprite = sprite;
}

Entity::Entity(int x, int y, int direction, std::string id, Sprite * sprite){
    this->id = id;
    this->entityX =  x;
    this->entityY =  y;
    this->direction = direction;
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
        int x_velocity = 4;
        if(this->direction == 270){
             SDL_Log("Here");
            x_velocity = -4;
        }
        bool colliding = isCollidingWithMap(map);
        // Check for collisions
        // Pass coords and height + width
        if(!colliding){
            this->entityX = this->entityX += x_velocity;
        }
        // this->entityX = this->entityX += 4;
    }
}

bool Entity::isCollidingWithMap(const std::vector<int>& map){

    // Calculate place on map
    // PASS IN LEVEL INSTEAD FOR MAPX (or width) use 17 for now

    // int xRounded = entityX / 64;
    //  q = (x + y - 1) / y;

    // Maybe if statements?
    int xRounded;
    if(this->direction == 90){
         xRounded = (entityX  + 63) / 64;
    } else{
         xRounded = entityX / 64;
    }
    int yRounded = entityY / 64;
    // int yRounded = (entityY  + 63) / 64;

    int levelMapIndex = (yRounded * 17) + xRounded;

    if(map[levelMapIndex] == 0){
        // SDL_Log("Thing: %d", xRounded);
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
