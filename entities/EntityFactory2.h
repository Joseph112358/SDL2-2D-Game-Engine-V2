#pragma once
#include <string>
#include "Entity2.h"
#include "SpriteFactory.h"

class EntityFactory2 {
public:
    EntityFactory2();
    ~EntityFactory2();

    Entity2* createEntity(const std::string& type, int x, int y, int direction = 90);

private:
    SpriteFactory* spriteFactory;
};
