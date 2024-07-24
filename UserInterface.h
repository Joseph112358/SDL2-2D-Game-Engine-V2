#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>
#include <queue>


class UserInterface {
    public:
        UserInterface();
        bool isInventoryShown;


        void toggleInventoryShown();
        void drawInventoryMenu(SDL_Renderer * renderer);
};