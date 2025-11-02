#include <unordered_map>
#include "../Sprite.h"
#include "SpriteFactory.h"
#include <string>


SpriteFactory::SpriteFactory(){
    spriteMap = std::unordered_map<std::string, Sprite*>();
}

Sprite* SpriteFactory::getSprite(std::string key){
    auto it = spriteMap.find(key);
    if (it != spriteMap.end()) {
        return it->second;
    }

    if(key == "fireball"){
        Sprite * fireball_sprite = new Sprite(0,16,32,16,32,64);
        spriteMap["fireball"] = fireball_sprite;
        return fireball_sprite; 
    }
    else if(key == "enemy"){
        Sprite * enemy_sprite = new Sprite(32,0,32,32,64,64);
        spriteMap["enemy"] = enemy_sprite; 
        return enemy_sprite;
    } 
    
    else {
        return nullptr; // Example, replace with your desired behavior
      }
  
}