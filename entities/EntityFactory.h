#ifndef ENTITY_FACTORY_H
#define ENTITY_FACTORY_H
#include <string>

#include "Entity.h"

class EntityFactory {
    public:
        EntityFactory();
        Entity * createEntity(std::string param, int x_pos, int y_pos);
        SpriteFactory * spriteFactory;
        
};

#endif