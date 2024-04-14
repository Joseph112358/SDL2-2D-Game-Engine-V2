#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstring>
#include <SDL.h>
#include <stdarg.h>
#include <SDL_image.h>
#include "Game.h"



Game *game = nullptr;

int main(int argc, char** args) {

const int FPS = 30;
const int frameDelay = 1000 / FPS;

Uint32 frameStart;
int frameTime;

  game  = new Game();
  game->init("Game", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1088,704,false);
  
  while(game->running()){

    frameStart = SDL_GetTicks();
    game->handleEvents();
    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;

  if(frameDelay > frameTime){
    SDL_Delay(frameDelay - frameTime);
  }
    
  }

  game->clean();

  return 0;
}