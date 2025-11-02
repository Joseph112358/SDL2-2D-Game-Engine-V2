// Enemy.h
#pragma once
#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(SDL_Rect rect, int direction, Sprite* sprite, int health = 100)
        : Entity(rect, direction, "enemy", sprite), health(health) {}

    void takeDamage(int dmg) {
        health -= dmg;
        if (health <= 0) alive = false;
    }

    bool isAlive() const { return alive; }

private:
    int health;
    bool alive = true;
};
