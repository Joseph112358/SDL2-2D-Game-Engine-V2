#pragma once
#include "../Sprite.h"
#include "../Level.h"
#include <SDL.h>
#include <string>

class Entity {
public:
    Entity(SDL_Rect rect, const std::string& id, Sprite* sprite);              // default direction
    Entity(SDL_Rect rect, int direction, const std::string& id, Sprite* sprite);

    virtual ~Entity() {}

    virtual void onCollision(Entity* other) {}  // Polymorphic

    virtual void update(Level* level);        // subclasses override
    // virtual void render(SDL_Renderer* renderer);
    virtual bool isCollidingWithMap(Level* level);

// protected:
    SDL_Rect rect;
    int direction;
    std::string id;
    int speed = 8;
    bool moving = false;
    Sprite* sprite = nullptr;
    

    void getSpriteTransform(SDL_RendererFlip& flip, double& rotation);

     // --- Deletion system ---
    void markForDeletion() { markedForDeletion = true; }
    bool isMarkedForDeletion() const { return markedForDeletion; }

    protected:
    bool markedForDeletion = false;
};
