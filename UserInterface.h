#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>
#include <queue>


class UserInterface {
    public:
        UserInterface();
        bool isInventoryShown;
        bool isInteractButtonShown;

        void drawInteractButton(SDL_Texture* itemsTexture,SDL_Renderer *renderer);
        void toggleInventoryShown();
        void drawInventoryMenu(SDL_Renderer * renderer);
};