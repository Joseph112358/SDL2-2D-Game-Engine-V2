#pragma once
#include "../Sprite.h"
#include "../Level.h"
#include <SDL.h>
#include <string>

class Entity2 {
public:
    Entity2(SDL_Rect rect, const std::string& id, Sprite* sprite);              // default direction
    Entity2(SDL_Rect rect, int direction, const std::string& id, Sprite* sprite);

    virtual ~Entity2() {}

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
};
