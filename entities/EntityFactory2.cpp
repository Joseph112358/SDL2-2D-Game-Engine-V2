#include "EntityFactory2.h"
#include "Fireball.h"
#include "Enemy.h"   // Make sure Enemy also inherits Entity2
#include <SDL.h>

EntityFactory2::EntityFactory2() {
    spriteFactory = new SpriteFactory();
}

EntityFactory2::~EntityFactory2() {
    delete spriteFactory;
}

Entity2* EntityFactory2::createEntity(const std::string& type, int x, int y, int direction) {
    if (type == "enemy") {
        Sprite* sprite = spriteFactory->getSprite("enemy");
        SDL_Rect rect = { x, y, 64, 64 };
        return new Enemy(rect, direction, sprite, 100);  // health = 100
    }
    else if (type == "fireball") {
        Sprite* sprite = spriteFactory->getSprite("fireball");
        SDL_Rect rect = { x, y, 64, 32 };
        return new Fireball(rect, direction, sprite);
    }

    // if (type == "fireball") {
    //     Sprite* sprite = spriteFactory->getSprite("fireball");
    //     SDL_Rect rect = { x, y, 64, 32 };
    //     return new Fireball(rect, direction, sprite);
    // }
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Unknown entity type: %s", type.c_str());
    return nullptr;
}
