// Enemy.h
#pragma once
#include "Entity2.h"

class Enemy : public Entity2 {
public:
    Enemy(SDL_Rect rect, int direction, Sprite* sprite, int health = 100)
        : Entity2(rect, direction, "enemy", sprite), health(health) {}

    void takeDamage(int dmg) {
        health -= dmg;
        if (health <= 0) alive = false;
    }

    bool isAlive() const { return alive; }

private:
    int health;
    bool alive = true;
};
