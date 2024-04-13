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

  game  = new Game();
  game->init("Game", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1088,640,false);
  
  while(game->running()){
    game->handleEvents();
    game->update();
    game->render();
  }

  game->clean();

  return 0;
}