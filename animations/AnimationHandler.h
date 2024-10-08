#include <iostream>
#include <SDL.h>
#include "../Player.h"
#include "Animations.h"

// Currently only for Player, but will be rewritten to support multiple sprite later.
class AnimationHandler {
      public:
        AnimationHandler();
        int currentFrame;
        int delay;
        void drawSprite(SDL_Renderer *renderer, Player * player);
        void drawPlayerWalkBox(SDL_Renderer *renderer);
};