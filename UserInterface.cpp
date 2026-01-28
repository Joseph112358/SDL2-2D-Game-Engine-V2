#include "UserInterface.h"
#include <stdio.h>
#include <SDL.h>

UserInterface::UserInterface(){
        this->isInventoryShown = false;
        this->isInteractButtonShown = false;
}

// current screen coords for reference: 1088,704

void UserInterface::drawWindow(SDL_Renderer* renderer, int w, int h, SDL_Color color){
    // Center the window automatically based on a standard 1080p or 720p target
    int screenW = 1088; // Ideally pass these in or use constants
    int screenH = 704;

    SDL_Rect rect = { (screenW - w) / 2, (screenH - h) / 2, w, h };

    // Background with transparency
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 200); 
    SDL_RenderFillRect(renderer, &rect);
    
    // Border
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);

}

void UserInterface::render(SDL_Renderer* renderer, SDL_Texture* uiTexture) {
    // 1. Draw the "Press E" prompt if needed
    if (isInteractButtonShown && activeMenu == MenuType::NONE) {
        drawInteractButton(uiTexture, renderer);
    }

    // 2. Draw active menus
    if (activeMenu == MenuType::CHEST) {
        drawWindow(renderer, 500, 400, {20, 20, 20}); // Dark grey chest window
        // Logic for drawing chest items goes here
    } 
    else if (activeMenu == MenuType::PLAYER_INVENTORY) {
        drawWindow(renderer, 600, 500, {10, 10, 40}); // Dark blue player window
    }
}

// Temporary fix for prototyping, really need to overhaul how textures are loaded and accessed
void UserInterface::drawInteractButton(SDL_Texture* itemsTexture,SDL_Renderer *renderer){
                SDL_Rect interactButtonAtlas {0, 32, 64, 16};
                SDL_Rect block {420, 600,256,64};
                SDL_RenderCopy(renderer,itemsTexture,&interactButtonAtlas,&block);

}

void UserInterface::drawInventoryMenu(SDL_Renderer * renderer){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Rect block { 64, 64,64,64};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128); // Set to red
    SDL_RenderFillRect(renderer, &block);
}

void UserInterface::toggleInventoryShown(){
    isInventoryShown = !isInventoryShown;
}
