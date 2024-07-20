#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>
#include <queue>


class UserInterface {
    public:
        UserInterface();
        bool isShown;


        void toggleShown();
        void drawUI(SDL_Renderer * renderer);
};