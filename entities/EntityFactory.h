#pragma once
#include <string>
#include "Entity.h"
#include "SpriteFactory.h"

class EntityFactory {
public:
    EntityFactory();
    ~EntityFactory();

    Entity* createEntity(const std::string& type, int x, int y, int direction = 90);

private:
    SpriteFactory* spriteFactory;
};
