#include "Enemy.h"
#include <SDL.h>

// Enemy(SDL_Rect rect, int direction, Sprite* sprite, int health = 4)
Enemy::Enemy(SDL_Rect rect, int direction, Sprite* sprite, int health)
    : Entity(rect, direction, "enemy", sprite), health(health), maxHealth(health) {
        int res = 2;
        SDL_Log("HERERERE");
        SDL_Log("Enemy constructed: health=%d, maxHealth=%d at %p", health, maxHealth, this);

    }


// void Enemy::update(Level* level) {
//     // TODO: basic AI, pathfinding, etc.
//     // For now, maybe idle or move toward the player?
// }

// void Enemy::takeDamage(int dmg) {
//     health -= dmg;
//     if (health <= 0) alive = false;
// }
