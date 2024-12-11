#include "Entity.h"
#include "EntityFactory.h"
#include <string>

EntityFactory::EntityFactory(){};

Entity * EntityFactory::createEntity(std::string param, int x_pos, int y_pos){
    if(param == "enemy"){
        Sprite * enemy_sprite = new Sprite(32,0,32,32,64,64);
        Entity * entity = new Entity(x_pos, y_pos, enemy_sprite);
        SDL_Log("enemy");
        return entity;

    }
    else if(param == "fireball"){
        Sprite * fireball_sprite = new Sprite(0,16,32,16,64,128);
        Entity * entity = new Entity(x_pos, y_pos, fireball_sprite);
        SDL_Log("fireball");
        return entity;
    }
};