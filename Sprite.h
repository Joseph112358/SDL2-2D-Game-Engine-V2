#pragma once
class Sprite {
    public:
        Sprite(int x, int y, int atlas_height, int atlas_width, int height, int width);
        int atlas_x;
        int atlas_y;
        int atlas_width;
        int atlas_height;
        int height;
        int width;
};