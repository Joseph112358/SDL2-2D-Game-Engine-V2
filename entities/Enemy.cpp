// Enemy.cpp
#include "Enemy.h"
#include <SDL.h>

void Enemy::update(Level* level) {
    // TODO: basic AI, pathfinding, etc.
    // For now, maybe idle or move toward the player?
}

void Enemy::takeDamage(int dmg) {
    health -= dmg;
    if (health <= 0) alive = false;
}
