#pragma once
#include "Entity.h"

class Fireball : public Entity {
public:
    Fireball(SDL_Rect rect, int direction, Sprite* sprite)
        : Entity(rect, direction, "fireball", sprite) {}

    void update(Level* level) override;
};
