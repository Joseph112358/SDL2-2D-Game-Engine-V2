#include "Fireball.h"
#include "../Level.h"

void Fireball::update(Level* level) {
    int x_velocity = 0;
    int y_velocity = 0;

    switch (direction) {
        case 90: x_velocity = speed; break;
        case 270: x_velocity = -speed; break;
        case 180: y_velocity = speed; break;
        default: y_velocity = -speed; break;
    }

    if (!isCollidingWithMap(level)) {
        rect.x += x_velocity;
        rect.y += y_velocity;
    }
}
