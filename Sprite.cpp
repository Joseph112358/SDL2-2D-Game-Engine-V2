#include "Sprite.h"

Sprite::Sprite(int x, int y, int atlas_height, int atlas_width, int height, int width){
    this->atlas_x =  x;
    this->atlas_y = y;
    this->atlas_width = atlas_width;
    this->atlas_height = atlas_height;
    this->height = height;
    this->width = width;
    

}
