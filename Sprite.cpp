#include "Sprite.h"

Sprite::Sprite(int atlas_x, int atlas_y, int atlas_height, int atlas_width, int height, int width){
    this->atlas_x =  atlas_x;
    this->atlas_y = atlas_y;
    this->atlas_width = atlas_width;
    this->atlas_height = atlas_height;
    this->height = height;
    this->width = width;
    

}
