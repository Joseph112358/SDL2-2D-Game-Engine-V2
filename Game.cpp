#include "Game.h"
#include <iostream>
#include <vector>
#include "Level.h"
#include "Player.h"
#include "Entity.h"
#include <cmath>
#include <queue>
#include <SDL_image.h>
#include "AnimationHandler.h"
SDL_Surface* atlasSurface = nullptr;
SDL_Surface* itemsSurface = nullptr;
SDL_Surface* entitiesSurface = nullptr;
SDL_Texture* atlasTexture = nullptr;
SDL_Texture* itemsTexture = nullptr;
SDL_Texture* entitiesTexture = nullptr;
Entity * entity = new Entity(64,64);
AnimationHandler * animationHandler = new AnimationHandler();

const Uint8 * keyState;
const int kMiddleOfScreenX = 512; const int kMiddleOfScreenY = 320;
const int kTileSize = 64;

Game::Game(){
};
Game::~Game(){

};

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){

    this->player = new Player();

    int flags = 0; 
    if(fullscreen){flags = SDL_WINDOW_FULLSCREEN;}

    SDL_Event e;
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(title, xpos, xpos, width, height, flags);
    renderer = SDL_CreateRenderer(window, -1, 0 );
    isRunning = true;

    this->level = new Level();

    std::pair<int,int> point(128, 128);
    std::pair<int,int> point2(192, 128);
    std::pair<int,int> point3(192, 192);
    std::pair<int,int> point4(256, 192);
    std::queue<std::pair<int,int>> coordQueue;
    coordQueue.push(point);
    coordQueue.push(point2);
    coordQueue.push(point3);
    coordQueue.push(point4);

    entity->moveQueue = coordQueue;
    
}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
    }

     handleKeyboardInput(event);

}

void Game::handleKeyboardInput(SDL_Event e){
     player->playerIdle = true;
    int playerMovementSpeed = 16;
    keyState = SDL_GetKeyboardState(NULL);
    if(keyState[SDL_SCANCODE_RIGHT]){
        this->player->playerX += playerMovementSpeed;
            player->direction = 90;
            player->playerIdle = false;
        // handlePlayerMovement()
    }
    else if(keyState[SDL_SCANCODE_LEFT]){
        this->player->playerX -= playerMovementSpeed;
            player->direction = 270;
            player->playerIdle = false;
    }
    if(keyState[SDL_SCANCODE_UP]){
        this->player->playerY -= playerMovementSpeed;
            player->direction = 0;
            player->playerIdle = false;
    }
    else if(keyState[SDL_SCANCODE_DOWN]){
        this->player->playerY += playerMovementSpeed;
            player->direction = 180;
              player->playerIdle = false;
    }

}

// Actually use this
void Game::update(){
    
    // TODO move to function in entity
    if(entity->moving){
        entity->moveToGivenPoint(entity->currentDestination, level->wallMap);
    }
    else if(entity->moveQueue.size() > 0){
        entity->moving = true;
        entity->currentDestination = entity->moveQueue.front();
        entity->moveToGivenPoint(entity->currentDestination, level->wallMap);
        entity->moveQueue.pop();
    }
}

void Game::drawMap(){

    int playerXoffset = player->playerX % 64;
    int playerYoffset = player->playerY % 64;
    // Camera system works, but is a little unintuitive
    // Extract to tiny function?
    atlasSurface = IMG_Load("res/Atlas3.png");
    atlasTexture = SDL_CreateTextureFromSurface(renderer, atlasSurface);
    itemsSurface = IMG_Load("res/items-sprite-v1.png");
    itemsTexture = SDL_CreateTextureFromSurface(renderer, itemsSurface);
    for(int i = -512; i < 640; i+= 64){
        for(int j = -320; j < 448; j+=64){
            int currentSquareX = kMiddleOfScreenX + (i) - playerXoffset;
            int currentSquareY = kMiddleOfScreenY + (j) - playerYoffset;
      

            int currentTileX =(this->player->playerX /64)  + (i / 64);


           
            int currentTileY = (this->player->playerY/64) + (j /64);
       
            int currentTile = currentTileY*this->level->mapX+currentTileX;
        
            SDL_Rect currentTileDimensions {currentSquareX, currentSquareY,kTileSize,kTileSize};


            // Extract to tiny function?
            bool inMap = this->level->inMap(currentTileX, currentTileY);
            if(inMap){
            // Draw Floor
            if(this->level->floorMap.at(currentTile) == 1){
                SDL_Rect block {currentSquareX, currentSquareY,kTileSize,kTileSize};
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
                SDL_RenderFillRect(renderer, &block);
            } else {
                SDL_Rect block {currentSquareX, currentSquareY,kTileSize,kTileSize};
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &block);
            }

            // Draw items

            if(this->level->itemMap.at(currentTile) == 1){
                SDL_Rect block {currentSquareX, currentSquareY,kTileSize,kTileSize};
                SDL_Rect atlasCoords {0,0,16,16};
                SDL_RenderCopy(renderer,itemsTexture,&atlasCoords,&currentTileDimensions);
              }

            // Draw Walls
            if(this->level->wallMap.at(currentTile) == 1){
                SDL_Rect block {currentSquareX, currentSquareY,kTileSize,kTileSize};
                SDL_RenderCopy(renderer,atlasTexture,NULL,&currentTileDimensions);
              }
            }
            else {
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_Rect block {currentSquareX, currentSquareY,kTileSize,kTileSize};
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
    
}

void Game::render(){
    SDL_RenderSetLogicalSize(renderer, 1088, 704);
    SDL_RenderClear(renderer);

    drawMap();
    //   Draw floor
    //   Draw floor items
    //   Draw walls


    // Draw entites (eventually)
    // drawEntities(Level * level)... for entity in levels ...
    drawEntity(entity);

    SDL_DestroyTexture(atlasTexture);
    SDL_DestroyTexture(itemsTexture);
    SDL_DestroyTexture(entitiesTexture);
    SDL_FreeSurface(atlasSurface);
    SDL_FreeSurface(itemsSurface);
    SDL_FreeSurface(entitiesSurface);

    
    renderPlayer(this->player);
    
    std::pair<int,int> playerCoords(this->player->playerX, this->player->playerY);
    checkCollisions(playerCoords);

    std::vector<int> PlayerAdjacent = player->getNeighborTiles(level->wallMap, level->mapX);
    for(int tile: PlayerAdjacent){
        drawTileBox(tile);
    }

    SDL_RenderPresent(renderer);
}

void Game::renderPlayer(Player * player){

    animationHandler->drawSprite(renderer, player);
  
}


// Eventually replace with a draw active items maybe?
void Game::drawEntity(Entity * entity){

    entitiesSurface = IMG_Load("res/entities-sprite-v1.png");
    entitiesTexture = SDL_CreateTextureFromSurface(renderer, entitiesSurface);

    // Work out distance to player
    int xOffset = entity->entityX - player->playerX; 
    int yOffset = entity->entityY - player->playerY;
    // check if in range maybe?
    int entityScreenX = kMiddleOfScreenX + xOffset;
    int entityScreenY = kMiddleOfScreenY + yOffset;

    SDL_Rect block { entityScreenX, entityScreenY,64,64};
    SDL_RenderCopy(renderer,entitiesTexture,NULL,&block);
 
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
void Game::drawCollisionbox(int boxX, int boxY){

    int relativeBoxTopLeftX = (boxX  * kTileSize) - player->playerX;
    int relativeBoxTopLeftY = (boxY  * kTileSize) - player->playerY;

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
    int mapX = 17;
    int y = arrayLocation/mapX;
    int x = arrayLocation%mapX;
    return std::pair<int,int> {x, y};
}

int coordsToArrayInt(std::pair<int, int> coords){
    int mapX = 17;
    return coords.first + mapX*coords.second;
}