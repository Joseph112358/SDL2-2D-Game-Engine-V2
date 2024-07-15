#include "AnimationHandler.h"
#include <SDL_image.h>

AnimationHandler::AnimationHandler(){
    this->animationFrame = 1;
}

void AnimationHandler::drawSprite(SDL_Renderer *renderer, Player * player){

    SDL_Surface* tmpSurface = IMG_Load("res/player-sprite-v1.png");
    SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    int atlasYPos = 0;
    switch (player->direction){
        case 90: // do right animation
            atlasYPos = 0;
            this->animationFrame == 6 ? animationFrame = 1 : animationFrame++;
            break;
        case 270: // Do left animation
            atlasYPos = 1;
            this->animationFrame == 6 ? animationFrame = 1 : animationFrame++;
            break;
        case 0:
            atlasYPos = 2;
            this->animationFrame == 6 ? animationFrame = 1 : animationFrame++;
            break;
        case 180:
            atlasYPos = 3;
               this->animationFrame == 6 ? animationFrame = 1 : animationFrame++;
            break;
        default:
            break;
    }
    if(player->playerIdle) animationFrame = 0, atlasYPos = 0;

    SDL_Rect playerAtlasCoords {animationFrame * 32, atlasYPos * 32, 32, 32};
    // 512 - 32 so more middle of screen
    SDL_Rect block {512,320,64,64};
    SDL_RenderCopy(renderer,tmpTexture,&playerAtlasCoords,&block);

    SDL_DestroyTexture(tmpTexture);
    SDL_FreeSurface(tmpSurface);

    drawPlayerWalkBox(renderer);
}


void AnimationHandler::drawPlayerWalkBox(SDL_Renderer *renderer){

    SDL_SetRenderDrawColor(renderer,255,0,0,255); // Yellow
    // Left border
    SDL_Rect block {512 , 352,3,32}; // Top
    SDL_RenderFillRect(renderer, &block);
     // Right border
    block  = {512 + 61 , 352 ,3,32}; // Top
    SDL_RenderFillRect(renderer, &block);
    // Top border
    block  = {512 , 352,64,3}; // Top
    SDL_RenderFillRect(renderer, &block);
    // Bottom border
    block  = {512 , 352+32,64,3}; // Top
    SDL_RenderFillRect(renderer, &block);
}