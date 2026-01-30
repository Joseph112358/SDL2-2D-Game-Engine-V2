// Interactables.hpp
#pragma once
#include "IInteractable.hpp"
#include <iostream>
#include <SDL.h>

class Chest : public IInteractable {
public:
    
    void onInteract() override { 
        SDL_Log("Opened chest!\n");
    }
    
    Item* storage[10]; // This chest's specific items

  
    Chest() {
        for(int i = 0; i < 10; i++) storage[i] = nullptr;
        storage[0] = new Item{"fireball", 16, 16}; 
    }
    
    int getAtlasX() const override { return 0; } // First icon in your atlas
    std::string getInteractPrompt() const override { return "Open Chest [E]"; } // These are obsolete atm

   MenuType getAssociatedMenu() override { 
        return MenuType::CHEST; 
    }

};

class Lever : public IInteractable {
public:
    void onInteract() override { std::cout << "Pulled lever!\n"; }
    int getAtlasX() const override { return 32; } // Third icon in your atlas
    std::string getInteractPrompt() const override { return "Pull Lever [E]"; }
};