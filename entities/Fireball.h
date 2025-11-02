#pragma once
#include "Entity2.h"

class Fireball : public Entity2 {
public:
    Fireball(SDL_Rect rect, int direction, Sprite* sprite)
        : Entity2(rect, direction, "fireball", sprite) {}

    void update(Level* level) override;
};
