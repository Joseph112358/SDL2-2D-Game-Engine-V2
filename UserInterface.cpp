#include "UserInterface.h"
#include <stdio.h>
#include <SDL.h>

UserInterface::UserInterface(){
        this->isInventoryShown = false;
        this->isInteractButtonShown = false;
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
