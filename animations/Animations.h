#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>

// A data class to hold animation data
class Animations {
    public:
        Animations();
        std::vector<std::pair<int,int>> rightFrames;
        std::vector<std::pair<int,int>> leftFrames;
        std::vector<std::pair<int,int>> upFrames;
        std::vector<std::pair<int,int>> downFrames;
        std::vector<std::pair<int,int>> idleFrames;
};