#include "Fireball.h"
#include "Entity.h"
#include "../Level.h"
#include "Enemy.h"
#include <SDL.h>


void Fireball::update(Level* level) {
    int x_velocity = 0;
    int y_velocity = 0;

    switch (direction) {
        case 90: x_velocity = speed; break;
        case 270: x_velocity = -speed; break;
        case 180: y_velocity = speed; break;
        default: y_velocity = -speed; break;
    }

    if(isCollidingWithMap(level)) {
        SDL_Log("Collision with map detected");
        markForDeletion();
    } else {
        rect.x += x_velocity;
        rect.y += y_velocity;
    }
}

void Fireball::onCollision(Entity* other) {
    // Only care if it hits an enemy
    if (Enemy* enemy = dynamic_cast<Enemy*>(other)) {
        SDL_Log("Fireball hit an enemy!");
        enemy->takeDamage(1);  // Or whatever method you have
        markForDeletion();      // Destroy fireball after hitting
    }
}
