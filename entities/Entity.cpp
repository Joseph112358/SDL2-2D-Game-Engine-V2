#include "Entity.h"
#include "../Sprite.h"
#include <SDL.h>
#include "../Level.h"
#include <cmath>

enum EntityType { FIREBALL, ENEMY };

int entityMoveSpeed = 4;
Entity::Entity(SDL_Rect rect, std::string id, Sprite * sprite){
    this->id = id;
    // this->entityX =  x;
    // this->entityY =  y;
    this->rect = rect;
    this->direction = 90;
    this->moving = false;
    this->sprite = sprite;
}

Entity::Entity(SDL_Rect rect, int direction, std::string id, Sprite * sprite){
    this->id = id;
    this->rect = rect;
    this->direction = direction;
    
    // Hacky way of sorting out rotated collision box
    if(direction == 0 || direction == 180){
        this->rect.w = sprite->height;
        this->rect.h = sprite->width;
    } else {
        this->rect.w = sprite->width;
        this->rect.h = sprite->height;
    }

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

 
    // Check if colliding with other entities?
    // Check for collisions with the map
    if (!isCollidingWithMap(level)) {
        // Update entity coordinates if no collision
        this->rect.x += x_velocity;
        this->rect.y += y_velocity;
    }
}
}

// Lord have mercy for the code I have written below
// Redesign or refactor -> we need to check all 4, or at least 2 corners
bool Entity::isCollidingWithMap(Level * level){
    const std::vector<int>& map = level->wallMap;
    int mapX = level->mapX;

    int xRounded = rect.x / 64;
    int yRounded = rect.y / 64;
    
    if (this->direction == 90) {
        xRounded = (rect.x + 63 + speed) / 64; // Moving right
    } else if (this->direction == 270) {
        xRounded = (rect.x - speed) / 64;        // Moving left
    }

    if (this->direction == 180) {
        yRounded = (rect.y + 63 + speed) / 64; // Moving down
    } else if (this->direction == 0) {
        yRounded = (rect.y - speed) / 64;        // Moving up
    }

    int levelMapIndex = (yRounded * mapX) + xRounded;

    // Check if the map cell is empty (0 indicates no collision)
    if(map[levelMapIndex] != 0) {return true;}
    
    // CHECKING THE OTHER CORNER

    xRounded = rect.x / 64;
    yRounded = rect.y / 64;
    
    // speed is the position you are next to occupy
    if (this->direction == 90) {
        xRounded = (rect.x + 63 + speed) / 64; // Moving right
        yRounded = (rect.y + 31) /64;
    } else if (this->direction == 270) {
        xRounded = (rect.x - speed) / 64;        // Moving left
        yRounded = (rect.y + 31) /64;
    }

    if (this->direction == 180) {
        yRounded = (rect.y + 63 + speed) / 64; // Moving down
        xRounded = (rect.x +31) /64;
    } else if (this->direction == 0) {
        yRounded = (rect.y - speed) / 64;        // Moving up
        xRounded = (rect.x +31) /64;
    }

    levelMapIndex = (yRounded * mapX) + xRounded;
    if(map[levelMapIndex] != 0) {return true;}

    return false;
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

