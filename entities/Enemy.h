#pragma once
#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(SDL_Rect rect, int direction, Sprite* sprite, int health = 4);

    void takeDamage(int dmg) {
        health -= dmg;
        if (health <= 0) alive = false, markForDeletion();
    }

    bool isAlive() const { return alive; }

    int getHealth() const { return health; }
    int getMaxHealth() const { return maxHealth; }

private:
    int health;
    int maxHealth;
    bool alive = true;
};
