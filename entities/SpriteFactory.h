#pragma once
#include <unordered_map>
#include "../Sprite.h"
#include <string>

class SpriteFactory {
    public:
    SpriteFactory();
    Sprite* getSprite(std::string key);
    std::unordered_map<std::string, Sprite *> spriteMap;  
};