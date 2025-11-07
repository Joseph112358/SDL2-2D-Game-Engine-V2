#include "EntityFactory.h"
#include "memory"
#include "Fireball.h"
#include "Enemy.h"   // Make sure Enemy also inherits Entity2
#include <SDL.h>

EntityFactory::EntityFactory() {
    spriteFactory = new SpriteFactory();
}

EntityFactory::~EntityFactory() {
    delete spriteFactory;
}

std::unique_ptr<Entity> EntityFactory::createEntity(const std::string& type, int x, int y, int direction) {
    if (type == "enemy") {
        SDL_Log("creating enemy here in the factory");
        Sprite* sprite = spriteFactory->getSprite("enemy");
        SDL_Rect rect = { x, y, 64, 64 };
        return std::make_unique<Enemy>(rect, direction, sprite, 4);  // health = 4
    }
    else if (type == "fireball") {
        Sprite* sprite = spriteFactory->getSprite("fireball");
        SDL_Rect rect = { x, y, 64, 32 };
        return std::make_unique<Fireball>(rect, direction, sprite);
    }

    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Unknown entity type: %s", type.c_str());
    return nullptr;
}
