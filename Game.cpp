#include "Game.h"
#include "Sprite.h"
#include <math.h> 
#include <iostream>
#include <vector>
#include "Level.h"
#include "Player.h"
#include "entities/Entity.h"
#include "UserInterface.h"
#include "entities/Enemy.h"
#include <cmath>
#include <queue>
#include <SDL_image.h>
#include "animations/AnimationHandler.h"
#include "Utils.h"
#include <list>
// TODO move all textures over to one atlas
// A texture loader might not be a bad idea?
SDL_Surface* atlasSurface = nullptr;
SDL_Surface* miscSurface = nullptr;
SDL_Surface* floorSurface = nullptr;
SDL_Texture* atlasTexture = nullptr;
SDL_Texture* miscTexture = nullptr;
SDL_Texture* floorTexture = nullptr;
AnimationHandler * animationHandler = new AnimationHandler();


bool collision_occuring = false;
bool clearEntities;

const Uint8 * keyState;
const int kMiddleOfScreenX = 512; const int kMiddleOfScreenY = 320;
const int TILE_UNIT_SIZE = 64;

Game::Game(){
    int joe = 2;
    // bool collision_occuring = false;
};
Game::~Game(){

};


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){

    this->player = new Player();
    this->userInterface = new UserInterface();
    this->entityFactory = new EntityFactory();

    // Temporary, have a list of interactables (store coords as key identifier for now
    // which the user can scroll through)

    this->interactablesList = std::list<int>();

    // Entity * entity_first = new Entity(320,320, enemy_sprite);
    // Entity * entity_first = entityFactory->createEntity("fireball", 0 , 0);
    // this->entities.push_back(entity_first);

    int flags = 0; 
    if(fullscreen){flags = SDL_WINDOW_FULLSCREEN;}

    SDL_Event e;
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(title, xpos, xpos, width, height, flags);
    renderer = SDL_CreateRenderer(window, -1, 0 );
    isRunning = true;

    this->level = new Level(0);
    
}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
    }
    
    // TODO: Rename functions so function / purpose is more understandable
     handleKeyboardInput(event); // Handle movement
     handleKeyInput(event);

}

void Game::handleKeyInput(SDL_Event e){
    if(e.type == SDL_KEYDOWN && SDL_PollEvent(&e)){
        if(e.key.keysym.sym == SDLK_m){
        this->userInterface->toggleInventoryShown();
        }
        if(e.key.keysym.sym == SDLK_e){
            // Get current floor tile and change its state?
            Entity * entity = entityFactory->createEntity("enemy", this->player->playerX , this->player->playerY);
            this->entities.push_back(entity);
        
        }
        if(e.key.keysym.sym == SDLK_f){
            
            Entity* entity = entityFactory->createEntity( "fireball", this->player->playerX,this->player->playerY,this->player->direction);
            this->entities.push_back(entity);
        }
         if(e.key.keysym.sym == SDLK_y){
            clearEntities = true;
         }
    }
 }

void Game::handleKeyboardInput(SDL_Event e){
    player->playerIdle = true;
    int playerMovementSpeed = 16;
    player->direction = 90;
    keyState = SDL_GetKeyboardState(NULL);

    if(keyState[SDL_SCANCODE_D]){
        player->playerIdle = false;
        player->direction = 90;
        player->handlePlayerMovement(90, this->level);
    }
    else if(keyState[SDL_SCANCODE_A]){
        player->handlePlayerMovement(270, this->level);
        player->direction = 270;
        player->playerIdle = false;
    }
    if(keyState[SDL_SCANCODE_W]){
        player->handlePlayerMovement(0, this->level);
         player->direction = 0;
        player->playerIdle = false;
    }
    else if(keyState[SDL_SCANCODE_S]){
        player->handlePlayerMovement(180, this->level);
         player->direction = 180;
        player->playerIdle = false;
    }
    if(keyState[SDL_SCANCODE_LSHIFT]){
        // Rewrite or something
        player->speed = 16;
    } else { player->speed = 8;}
}

// Actually use this
void Game::update(){

    if(clearEntities){

    for (auto& entity : entities) {
    delete entity;
    }

    entities.clear();
    clearEntities = false;
    }

    for (auto* entity : entities) {
    if (entity) {
        entity->update(this->level);
    }

    // TODO: Probably devise an algorithm to better solve this, otherwise always n*n
    collision_occuring = false;
    
    if(entities.size() >1){
        for(size_t i = 0; i < entities.size() -1; ++i){
            for(size_t j = i + 1; j < entities.size(); ++j){
                Entity* en1 = entities[i];
                Entity* en2 = entities[j];
                if (Utils::isCollidingAABB(en1->rect, en2->rect)) {
                    collision_occuring = true;
                // SDL_Log("Collision detected between entity %zu and %zu!", i, j);
                // Optionally handle collision here, e.g.:
                // en1->onCollision(en2);
                // en2->onCollision(en1);
                }
            }
     }
    }


    if(collision_occuring){
         SDL_Log("Collision detected!");
    }
}

    
}

void Game::drawMap(){
    // I think this is because the players coords are in multiples of 64, and need to be scaled down (to e.g. 3)
    int playerXoffset = player->playerX % TILE_UNIT_SIZE;
    int playerYoffset = player->playerY % TILE_UNIT_SIZE;
    // Camera system works, but is a little unintuitive
    // Extract to tiny function?

    for(int i = (-8 * TILE_UNIT_SIZE); i < (10* TILE_UNIT_SIZE); i+= 64){
        for(int j = (-5 *TILE_UNIT_SIZE); j < (7* TILE_UNIT_SIZE); j+=64){
            int currentSquareX = kMiddleOfScreenX + (i) - playerXoffset;
            int currentSquareY = kMiddleOfScreenY + (j) - playerYoffset;
      

            int currentTileX =(this->player->playerX /64)  + (i / 64);


           
            int currentTileY = (this->player->playerY/64) + (j /64);
       
            int currentTile = currentTileY*this->level->mapX+currentTileX;
        
            SDL_Rect currentTileDimensions {currentSquareX, currentSquareY,TILE_UNIT_SIZE,TILE_UNIT_SIZE};


            // Extract to tiny function?
            bool inMap = this->level->inMap(currentTileX, currentTileY);
            if(inMap){
            // Draw Floor
            if(this->level->floorMap.at(currentTile) == 1){

                SDL_Rect floorAtlasCoords {16, 0, 16, 16};
                // SDL_Rect block {currentSquareX, currentSquareY,TILE_UNIT_SIZE,TILE_UNIT_SIZE};
                SDL_RenderCopy(renderer,floorTexture,&floorAtlasCoords,&currentTileDimensions);
            } else {
                SDL_Rect floorAtlasCoords {32, 0, 16, 16};
               // SDL_Rect block {currentSquareX, currentSquareY,TILE_UNIT_SIZE,TILE_UNIT_SIZE};
                SDL_RenderCopy(renderer,floorTexture,&floorAtlasCoords,&currentTileDimensions);
            }

            // Draw items

            if(this->level->itemMap.at(currentTile) == 1){
                SDL_Rect block {currentSquareX, currentSquareY,TILE_UNIT_SIZE,TILE_UNIT_SIZE};

                // Test code
                int atlasOffset;

                // TODO: Rewrite this code so it makes more sense and is scalable
                std::pair<int, int> itemCoords = {currentTileX *64, currentTileY* 64};
                std::pair<int, int> playerCoords = {player->playerX, player->playerY};
                if (inRange(playerCoords,itemCoords)){
                     atlasOffset = 16;
                     this->userInterface->isInteractButtonShown = true;
                    // Add to an interactable queue of some kind?

                } else {
                    atlasOffset = 0;
                    this->userInterface->isInteractButtonShown = false;
                }

                
                SDL_Rect atlasCoords {atlasOffset,0,16,16};
                SDL_RenderCopy(renderer,miscTexture,&atlasCoords,&currentTileDimensions);
              }

            // Draw Walls
            if(this->level->wallMap.at(currentTile) == 1){
                SDL_Rect block {currentSquareX, currentSquareY,TILE_UNIT_SIZE,TILE_UNIT_SIZE};
                SDL_RenderCopy(renderer,atlasTexture,NULL,&currentTileDimensions);
              }
            }
            else {
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_Rect block {currentSquareX, currentSquareY,TILE_UNIT_SIZE,TILE_UNIT_SIZE};
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
    
    if(this->userInterface->isInteractButtonShown){
          this->userInterface->drawInteractButton(miscTexture, renderer);
    }
}

void Game::render(){
    SDL_RenderSetLogicalSize(renderer, 1088, 704);
    SDL_RenderClear(renderer);

    atlasSurface = IMG_Load("res/Atlas3.png");
    atlasTexture = SDL_CreateTextureFromSurface(renderer, atlasSurface);
    floorSurface = IMG_Load("res/desert.png");
    floorTexture = SDL_CreateTextureFromSurface(renderer, floorSurface);
    miscSurface = IMG_Load("res/misc.png");
    miscTexture = SDL_CreateTextureFromSurface(renderer, miscSurface);

    drawMap();
    //   Draw floor
    //   Draw floor items
    //   Draw walls

    drawEntities(this->entities);

    SDL_DestroyTexture(atlasTexture);
    SDL_DestroyTexture(floorTexture);
    SDL_DestroyTexture(miscTexture);
    SDL_FreeSurface(atlasSurface);
    SDL_FreeSurface(floorSurface);
    SDL_FreeSurface(miscSurface);


    
    renderPlayer(this->player);
    
    std::pair<int,int> playerCoords(this->player->playerX, this->player->playerY);
   checkCollisions(playerCoords);

    std::vector<int> PlayerAdjacent = player->getNeighborTiles(level->wallMap, level->mapX);
    // for(int tile: PlayerAdjacent){
    //     drawTileBox(tile);
    // }

    if(this->userInterface->isInventoryShown){
        this->userInterface->drawInventoryMenu(renderer);
    }
    SDL_RenderPresent(renderer);
}

void Game::renderPlayer(Player * player){

    animationHandler->drawSprite(renderer, player);
  
}


void Game::drawEntities(std::vector<Entity*> entities){
    for (Entity* entity : entities) {
        drawEntity(entity);
        // drawCollisionBox(entity->entityX,entity->entityY,entity->width,entity->height);
        drawCollisionBox(entity->rect.x,entity->rect.y,entity->rect.w,entity->rect.h);
    }

}



// This should not be here
void Game::drawEntity(Entity * entity){

    // Work out distance to player
    int xOffset = entity->rect.x - player->playerX; 
    int yOffset = entity->rect.y - player->playerY;
    // check if in range maybe?
    int entityScreenX = kMiddleOfScreenX + xOffset;
    int entityScreenY = kMiddleOfScreenY + yOffset;
   
    int entity_width = entity->rect.w;
    int entity_height = entity->rect.h;

    SDL_Rect block { entityScreenX, entityScreenY,entity_width,entity_height};
    if(entity->direction == 0 || entity->direction == 180){
        block.h = entity_width;
        block.w = entity_height;

        // Temp code fix
        block.x = entityScreenX - 16;
        block.y = entityScreenY + 16;
    }

    // flip code
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    double rotation = 0;
    entity->getSpriteTransform(flip, rotation);

    
    // Get the correct texture from the atlas
    //SDL_Rect AtlasCoords {entity->sprite->atlas_x, entity->sprite->atlas_y, entity->sprite->atlas_height, entity->sprite->atlas_width};
    SDL_Rect AtlasCoords {entity->sprite->atlas_x, entity->sprite->atlas_y, entity->sprite->atlas_height, entity->sprite->atlas_width};
    // SDL_RenderCopy(renderer,miscTexture,&AtlasCoords,&block);
    SDL_RenderCopyEx(renderer, miscTexture, &AtlasCoords, &block, rotation, nullptr, flip);


    // FIX THIS NOW!
    // ---- Draw health bar if entity is an Enemy ----
    if (Enemy* e = dynamic_cast<Enemy*>(entity)) {
    int barWidth = entity->sprite->width; // use original sprite width = 64
    // int barHeight = 5;
    // int x = block.x;
    // int y = block.y + block.h + 2;
    int x = entityScreenX;
    int y = entityScreenY + 64;

    SDL_Log("health: %d / %d", e->getHealth(), e->getMaxHealth());

    float healthFraction = static_cast<float>(e->getHealth()) / e->getMaxHealth();
    // SDL_Log("max health:  %d",  e->getHealth());
    int healthWidth = static_cast<int>(64 * healthFraction);

    // Red background
    // SDL_Rect bgRect = { x, y, barWidth, barHeight };
    SDL_Rect bgRect = { x, y, 64, 5 };
    SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
    SDL_RenderFillRect(renderer, &bgRect);

    // Green foreground
    // SDL_Rect fgRect = { x, y, healthWidth, barHeight };
    // SDL_Rect fgRect = { x, y, healthWidth, 5 };
    // SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    // SDL_RenderFillRect(renderer, &fgRect);
}
 
}

void Game::checkCollisions(std::pair<int,int> coords){
    bool isColliding = false;
    int XMin = coords.first / 64;
    int XMax = (coords.first+32) / 64;
    int YMin = coords.second / 64;
    int YMax = (coords.second + 48) / 64;
    if(this->level->wallMap.at(YMin*this->level->mapX+XMin) == 1){isColliding = true; drawCollisionbox(XMin,YMin);}
    if(this->level->wallMap.at(YMin*this->level->mapX+XMax) == 1){isColliding = true; drawCollisionbox(XMax,YMin);}
    if(this->level->wallMap.at(YMax*this->level->mapX+XMin) == 1){isColliding = true; drawCollisionbox(XMin,YMax);}
    if(this->level->wallMap.at(YMax*this->level->mapX+XMax) == 1){isColliding = true; drawCollisionbox(XMax,YMax);}
}

// Used for debugging mainly
void Game::drawCollisionBox(int boxX, int boxY, int width, int height){
    int xOffset = boxX - player->playerX; 
    int yOffset = boxY - player->playerY;

    int entityScreenX = kMiddleOfScreenX + xOffset;
    int entityScreenY = kMiddleOfScreenY + yOffset;

    SDL_Rect block { entityScreenX, entityScreenY,width,height};

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128); // RGBA: Red color
    SDL_RenderDrawRect(renderer, &block);
}
// [[deprecated]]
void Game::drawCollisionbox(int boxX, int boxY){

    int relativeBoxTopLeftX = (boxX  * TILE_UNIT_SIZE) - player->playerX;
    int relativeBoxTopLeftY = (boxY  * TILE_UNIT_SIZE) - player->playerY;

    SDL_SetRenderDrawColor(renderer,255,255,0,255); // Yellow
    // Left border
    SDL_Rect block {kMiddleOfScreenX + (int)(relativeBoxTopLeftX) , kMiddleOfScreenY + int(relativeBoxTopLeftY),3,64}; // Top
    SDL_RenderFillRect(renderer, &block);
     // Right border
    block  = {kMiddleOfScreenX + (int)(relativeBoxTopLeftX) + 61 , kMiddleOfScreenY + int(relativeBoxTopLeftY),3,64}; // Top
    SDL_RenderFillRect(renderer, &block);
    // Top border
    block  = {kMiddleOfScreenX + (int)(relativeBoxTopLeftX) , kMiddleOfScreenY + int(relativeBoxTopLeftY),64,3}; // Top
    SDL_RenderFillRect(renderer, &block);
    // Bottom border
    block  = {kMiddleOfScreenX + (int)(relativeBoxTopLeftX) , kMiddleOfScreenY + int(relativeBoxTopLeftY)+64,64,3}; // Top
    SDL_RenderFillRect(renderer, &block);
}

// Takes in a Tile reference point and draws a box there
void Game::drawTileBox(int tileIndex){
    std::pair<int,int> coords = arrayIntToPair(tileIndex);
    drawCollisionbox(coords.first, coords.second);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

std::pair<int,int> Game::arrayIntToPair(int arrayLocation){
    int mapX = this->level->mapX; // This should not be hard coded
    int y = arrayLocation/mapX;
    int x = arrayLocation%mapX;
    return std::pair<int,int> {x, y};
}

int Game::coordsToArrayInt(std::pair<int, int> coords){
    int mapX = this->level->mapX;
    return coords.first + mapX*coords.second;
}

bool Game::inRange(std::pair<int,int> playerPoint , std::pair<int,int> itemPoint) {
    double distance =sqrt(pow( playerPoint.first - itemPoint.first, 2) + pow(playerPoint.second - itemPoint.second, 2));
    return (distance < 91);
}

