// Enemy.cpp
#include "Enemy.h"
#include <SDL.h>

Enemy(SDL_Rect rect, int direction, Sprite* sprite, int health = 4)
    : Entity(rect, direction, "enemy", sprite), health(health), maxHealth(health) {}

void Enemy::update(Level* level) {
    // TODO: basic AI, pathfinding, etc.
    // For now, maybe idle or move toward the player?
}

void Enemy::takeDamage(int dmg) {
    health -= dmg;
    if (health <= 0) alive = false;
}
