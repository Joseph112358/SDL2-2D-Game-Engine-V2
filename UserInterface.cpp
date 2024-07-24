#include "UserInterface.h"
#include <stdio.h>
#include <SDL.h>

UserInterface::UserInterface(){
        this->isInventoryShown = false;
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
