#include "Entity.h"
#include "EntityFactory.h"
#include "SpriteFactory.h"
#include <string>

EntityFactory::EntityFactory(){
    this->spriteFactory = new SpriteFactory();
};

Entity * EntityFactory::createEntity(std::string param, int x_pos, int y_pos, int direction){
    if(param == "enemy"){
        Sprite * enemy_sprite = spriteFactory->getSprite("enemy");
        SDL_Rect rect = {x_pos, y_pos, 64, 64};
        Entity * entity = new Entity(rect, direction, param ,enemy_sprite);
        SDL_Log("enemy");
        return entity;

    }
    else if(param == "fireball"){
        Sprite * fireball_sprite = spriteFactory->getSprite("fireball");
        SDL_Rect rect = {x_pos, y_pos, 64, 32};
        Entity * entity = new Entity(rect, direction, param, fireball_sprite);
        SDL_Log("fireball");
        return entity;
    }
};

Entity* EntityFactory::createEntity(std::string param, int x_pos, int y_pos) {
    return createEntity(param, x_pos, y_pos, 90); // Call the overloaded function with default direction
}