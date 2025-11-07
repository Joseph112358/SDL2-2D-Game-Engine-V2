#include "Entity.h"
#include <vector>

Entity::Entity(SDL_Rect rect, const std::string& id, Sprite* sprite)
    : rect(rect), id(id), sprite(sprite), direction(0), moving(false), speed(8) {
        // SDL_Log("Here in entity 1");
    }

Entity::Entity(SDL_Rect rect, int direction, const std::string& id, Sprite* sprite)
    : rect(rect), id(id), sprite(sprite), direction(direction), moving(false), speed(8)
{
    // SDL_Log("Here in entity 2");

    if (direction == 0 || direction == 180) {
        // swap width and height for vertical movement
        std::swap(this->rect.w, this->rect.h);
    }
}


void Entity::update(Level* level) {
    // Base does nothing; subclasses override
}


// Lord have mercy for the code I have written below
// Redesign or refactor -> we need to check all 4, or at least 2 corners
// --> The above was copied over from previous attemtps, idk anymore
bool Entity::isCollidingWithMap(Level* level) {
    const std::vector<int>& map = level->wallMap;
    int mapX = level->mapX;

    // Calculate the next position based on speed & direction
    int nextX = rect.x;
    int nextY = rect.y;

    switch (direction) {
        case 90:  nextX += speed; break;   // moving right
        case 270: nextX -= speed; break;   // moving left
        case 180: nextY += speed; break;   // moving down
        case 0:   nextY -= speed; break;   // moving up
    }

    // Check the four corners of the rectangle after movement
    int cornersX[2] = { nextX, nextX + rect.w - 1 };
    int cornersY[2] = { nextY, nextY + rect.h - 1 };

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int mapCellX = cornersX[i] / 64;
            int mapCellY = cornersY[j] / 64;
            int index = mapCellY * mapX + mapCellX;

            if (index < 0 || index >= map.size()) continue; // bounds check
            if (map[index] != 0) return true; // collision detected
        }
    }

    return false;
}

// void Entity2::getSpriteTransform(SDL_RendererFlip& flip, double& rotation) {
//     flip = SDL_FLIP_NONE;
//     rotation = 0;
// }


// Maybe this should be in Fireball?
// Maybe this should definitly be in Sprite?
void Entity::getSpriteTransform(SDL_RendererFlip& flip, double& rotation){
    switch (direction) {
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
