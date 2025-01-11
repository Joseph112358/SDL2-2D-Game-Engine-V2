#include "Entity.h"
#include "../Sprite.h"
#include <SDL.h>
#include "../Level.h"
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
    this->speed = 8;
    this->moving = false;
    this->sprite = sprite;
}

// Maybe add a list of points to visit / process?

// Have components instead e.g. for entity, apply compenent effect (movement etc) if valid (e.g. in motion)

// Check for collisions
//   if yes, explode -> whatever this should be
//   if no move forward


void Entity::update(Level * level){

if (this->id == "fireball") {
       // Initialize velocity components
    int x_velocity = 0;
    int y_velocity = 0;

    // Determine velocity based on direction
    switch (this->direction) {
        case 90:  x_velocity = speed;  break;
        case 270: x_velocity = -1 * speed; break;
        case 180: y_velocity = speed;  break;
        default:  y_velocity = -1 * speed; break;
    }

    // Check for collisions with the map
    if (!isCollidingWithMap(level)) {
        // Update entity coordinates if no collision
        this->entityX += x_velocity;
        this->entityY += y_velocity;
    }
}
}

// PASS IN LEVEL INSTEAD FOR MAPX (or width) use 17 for now
bool Entity::isCollidingWithMap(Level * level){
    const std::vector<int>& map = level->wallMap;
    int mapX = level->mapX;

    int xRounded = entityX / 64;
    int yRounded = entityY / 64;
    
    if (this->direction == 90) {
        xRounded = (entityX + 63 + speed) / 64; // Moving right
    } else if (this->direction == 270) {
        xRounded = (entityX - speed) / 64;        // Moving left
    }

    if (this->direction == 180) {
        yRounded = (entityY + 63 + speed) / 64; // Moving down
    } else if (this->direction == 0) {
        yRounded = (entityY - speed) / 64;        // Moving up
    }

    int levelMapIndex = (yRounded * 17) + xRounded;

    // Check if the map cell is empty (0 indicates no collision)
    return map[levelMapIndex] != 0;
}

void Entity::getSpriteTransform(SDL_RendererFlip& flip, double& rotation){
        switch (this->direction) {
            case 90:
                flip = SDL_FLIP_NONE;
                rotation = 0;
                break;
            case 270:
                flip = SDL_FLIP_HORIZONTAL;
                rotation = 0;
                break;
            case 180:
                flip = SDL_FLIP_NONE;
                rotation = 90;
                break;
            case 0:
            default:
                flip = SDL_FLIP_NONE;
                rotation = 270;
                break;
        }
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
