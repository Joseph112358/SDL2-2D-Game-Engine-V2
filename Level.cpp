#include "Level.h"
#include "game_objects/InteractableObject.h"
#include <iostream>
#include <vector>
 // Needs to store
    // Floor layout (layer 0)
    // Room layout (layer 1)
    // Wall layout
    // Objects in room
    // Aspirational: Room dimensions

Level::Level(int levelCode){

   if(levelCode == 0){
   this->mapX = 17;
   this->mapY = 10;
   this->wallMap = * new std::vector<int> 
         {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
          1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
          1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,
          1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,
          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
          1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
          1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
          1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
          1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1                     
         };
   this->floorMap = * new std::vector<int> 
         {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
          0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
          1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
          0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
          1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
          0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
          1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
          0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
          1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
          0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,                    
         };
   this->itemMap = * new std::vector<int> 
         {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
          0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,                    
         };
   }
   else {
      this->mapX = 6;
      this->mapY = 6;
      this->wallMap = * new std::vector<int> 
         {1,1,1,1,1,1,
          1,0,0,0,0,1,
          1,0,0,0,0,1,
          1,0,0,0,0,1,
          1,0,0,0,0,1,
          1,1,1,1,1,1,                
         };
   this->floorMap = * new std::vector<int> 
         {1,0,1,0,1,0,
          1,0,1,0,1,0,
          1,0,1,0,1,0,
          1,0,1,0,1,0,
          1,0,1,0,1,0,
          1,0,1,0,1,0,                
         };
   this->itemMap = * new std::vector<int> 
         {0,0,0,0,0,0,
         0,0,0,0,0,0,
         0,0,0,0,0,0,
         0,0,0,0,0,0,
         0,0,0,0,0,0,
         0,0,0,0,0,0,
         };
   }
}

// Create level from config file?


Level::Level(int mapX, int mapY, std::vector<int> floorMap,std::vector<int> wallMap){
   this->mapX = mapX;
   this->mapY = mapY;
   this->floorMap = floorMap;
   this->wallMap = wallMap;
}

bool Level::inMap(int x, int y){
   bool inMap = true;
   if(x > this->mapX -1 || x < 0 || y > this->mapY -1 || y < 0) inMap = false;
   return inMap;
}
int Level::getMapX(){
   return mapX;
}
