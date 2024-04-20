#include <iostream>
#include <SDL.h>
#include "Player.h"

// Currently only for Player, but will be rewritten to support multiple sprite later.
class AnimationHandler {
      public:
        AnimationHandler();
        int animationFrame;
        int atlasYpos;
        void drawSprite(SDL_Renderer *renderer, Player * player);
};