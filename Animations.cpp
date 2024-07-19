#include "Animations.h"
#include <vector>

Animations::Animations(){
    this->rightFrames = {{32,0},{64,0},{96,0},{128,0},{160,0},{192,0}};
    this->leftFrames =  {{32,32},{64,32},{96,32},{128,32},{160,32},{192,32}};
    this->upFrames = {{32,64},{64,64},{96,64},{128,64},{160,64},{192,64}};
    this->downFrames = {{32,96},{64,96},{96,96},{128,96},{160,96},{192,96}};
    this->idleFrames = {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}};
}

