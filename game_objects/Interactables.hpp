// Interactables.hpp
#pragma once
#include "IInteractable.hpp"
#include <iostream>
#include <SDL.h>

class Chest : public IInteractable {
public:
    // Move this to SDL log
    void onInteract() override { 

        SDL_Log("Opened chest!\n");
        // std::cout << "Opened chest!\n"; 
        }
    int getAtlasX() const override { return 0; } // First icon in your atlas
    std::string getInteractPrompt() const override { return "Open Chest [E]"; } // These are obsolete atm
};

class Lever : public IInteractable {
public:
    void onInteract() override { std::cout << "Pulled lever!\n"; }
    int getAtlasX() const override { return 32; } // Third icon in your atlas
    std::string getInteractPrompt() const override { return "Pull Lever [E]"; }
};