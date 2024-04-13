#include "Level.h"
#include <iostream>
#include <vector>
 // Needs to store
    // Floor layout (layer 0)
    // Room layout (layer 1)
    // Wall layout
    // Objects in room
    // Aspirational: Room dimensions

Level::Level(){
   this->mapX = 17;
   this->mapY = 10;
   this->floorMap = * new std::vector<int> 
         {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
          1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
          1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
          1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
          1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
          1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
          1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1                     
         };
}

Level::Level(int mapX, int mapY, std::vector<int> floorMap,std::vector<int> itemMap){
   this->mapX = mapX;
   this->mapY = mapY;
   this->floorMap = floorMap;
   this->itemMap = itemMap;
}

int Level::getMapX(){
   return mapX;
}
