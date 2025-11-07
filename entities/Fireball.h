#pragma once
#include "Entity.h"
#include <SDL.h>

class Fireball : public Entity {
public:
    Fireball(SDL_Rect rect, int direction, Sprite* sprite)
        : Entity(rect, direction, "fireball", sprite) {
            SDL_Log("Creating fireball");
        }

    void update(Level* level) override;
};
