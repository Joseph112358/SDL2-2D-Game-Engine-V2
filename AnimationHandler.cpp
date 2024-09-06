#include "AnimationHandler.h"
#include "Animations.h"
#include <SDL_image.h>

AnimationHandler::AnimationHandler(){
    this->currentFrame = 1;
    this->delay = 0;
}

void AnimationHandler::drawSprite(SDL_Renderer *renderer, Player * player){

    Animations animations = player->animations;
    std::vector<std::pair<int,int>> frames;

    SDL_Surface* tmpSurface = IMG_Load("res/player-sprite-v1.png");
    SDL_Texture* tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);

    switch (player->direction){
        case 90: // do right animation
            frames = animations.rightFrames;
            break;
        case 270: // Do left animation
            frames = animations.leftFrames;
            break;
        case 0:
            frames = animations.upFrames;
            break;
        case 180:
            frames = animations.downFrames;
            break;
        default:
            break;
    }

    // Animations too fast, not sure if delta related
    delay == 2? delay = 0 : delay++;
    if(delay == 0 ){
    currentFrame == 5? currentFrame = 1 : currentFrame++;
    }


    if(player->playerIdle) frames = animations.idleFrames;
    std::pair<int,int> animationCoords = frames.at(currentFrame);

    SDL_Rect playerAtlasCoords {animationCoords.first, animationCoords.second, 32, 32};
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