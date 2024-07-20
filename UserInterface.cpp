#include "UserInterface.h"
#include <stdio.h>
#include <SDL.h>

UserInterface::UserInterface(){
        this->isShown = false;
}


void UserInterface::drawUI(SDL_Renderer * renderer){
    SDL_Rect block { 64, 64,64,64};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set to red
    SDL_RenderFillRect(renderer, &block);
}

void UserInterface::toggleShown(){
    isShown = !isShown;
}
