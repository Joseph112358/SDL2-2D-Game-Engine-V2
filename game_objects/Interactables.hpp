// Interactables.hpp
#pragma once
#include "IInteractable.hpp"
#include <iostream>
#include "./../GameTypes.h"
#include <SDL.h>

class UserInterface; // this is temp probs

class Chest : public IInteractable {
public:
    Inventory storage;

    Chest() {
        for (int i = 0; i < 10; i++) {
            storage.slots[i] = nullptr;
        }
        storage.slots[0] = new Item{"fireball", 0, 16}; 
        storage.slots[1] = new Item{"fireball", 0, 16};
    }

    ~Chest() {
        for (int i = 0; i < 10; i++) {
            delete storage.slots[i]; // Clean up the items we created
        }
    }

    InteractionResult onInteract() override {
        SDL_Log("Chest opened!");
        return InteractionResult::Open(&this->storage);
    }
    
    int getAtlasX() const override { return 0; } // First icon in your atlas
    std::string getInteractPrompt() const override { return "Open Chest [E]"; } // These are obsolete atm

   MenuType getAssociatedMenu() override { 
        return MenuType::CHEST; 
    }

};

class Lever : public IInteractable {
public:
     
    InteractionResult onInteract() override {
        SDL_Log("Chest interacted with.");
        return InteractionResult{ InteractionType::None, nullptr };
    }

    int getAtlasX() const override { return 32; } // Third icon in your atlas
    std::string getInteractPrompt() const override { return "Pull Lever [E]"; }
};