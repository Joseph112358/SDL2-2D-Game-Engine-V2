#include "Fireball.h"
#include <cmath>

int entityMoveSpeed = 4;
Fireball::Fireball(int x, int y){
    this->x_pos =  x;
    this->y_pos =  y;
}


void Fireball::update(){
    this->x_pos = this->x_pos += 2;
}

