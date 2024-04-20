#include "Game.h"
#include <iostream>
#include <vector>
#include "Level.h"
#include "Player.h"
#include <cmath>
#include <SDL_image.h>
#include "AnimationHandler.h"
int middleOfScreenX = 512; int middleOfScreenY = 320;
SDL_Surface* tmpSurface = nullptr;
SDL_Texture* tmpTexture = nullptr;
AnimationHandler * animationHandler = new AnimationHandler();

const Uint8 * keyState;

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
 
    keyState = SDL_GetKeyboardState(NULL);
    if(keyState[SDL_SCANCODE_RIGHT]){
        this->player->playerX += 0.25;
            player->direction = 90;
            player->playerIdle = false;
        // handlePlayerMovement()
    }
    else if(keyState[SDL_SCANCODE_LEFT]){
        this->player->playerX -= 0.25;
            player->direction = 270;
            player->playerIdle = false;
    }
    if(keyState[SDL_SCANCODE_UP]){
        this->player->playerY -= 0.25;
            player->direction = 0;
            player->playerIdle = false;
    }
    else if(keyState[SDL_SCANCODE_DOWN]){
        this->player->playerY += 0.25;
            player->direction = 180;
              player->playerIdle = false;
    }

}

// Actually use this
void Game::update(){

}

// Get rid of floor drawing
// We can merge all drawing stuff
void Game::drawMap(){
    int playerXIntegerPart = static_cast<int>(player->playerX);
    float playerXFloatPart = player->playerX - playerXIntegerPart;
    int playerYIntegerPart = static_cast<int>(player->playerY);
    float playerYFloatPart = player->playerY - playerYIntegerPart;
    
    // Camera system works, but is a little unintuitive
    // Extract to tiny function?
    tmpSurface = IMG_Load("res/Atlas3.png");
    tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    for(int i = -8; i < 10; i++){
        for(int j = -5; j < 7; j++){
            int currentSquareX = middleOfScreenX + (i *64) - (playerXFloatPart * 64)  ; // change var name, maybe tileScreenCoords?
            int currentSquareY = middleOfScreenY + (j *64) - (playerYFloatPart * 64);
            
            // Weird workaround code
            // If currentTileX = -0.5, it rounds to 0 which is technically in bounds, when it shouldn't be
            // Hence, without this code, the first out of bounds area renders incorrectly.
            int currentTileX;
            if((float)player->playerX+i < 0){
                currentTileX = -1;
            }
            else {
                currentTileX = this->player->playerX+i;
            }

            int currentTileY;
            if((float)player->playerY+j < 0){
                currentTileY = -1;
            } else {
                 currentTileY = this->player->playerY+j;
            }
            int currentTile = currentTileY*this->level->mapX+currentTileX;
        
            SDL_Rect currentTileDimensions {currentSquareX, currentSquareY,64,64};

            // End of workaround tile code

            // Extract to tiny function?
            bool inMap = this->level->inMap(currentTileX, currentTileY);
            if(inMap){
            // Draw Floor
            if(this->level->floorMap.at(currentTile) == 1){
                SDL_Rect block {currentSquareX, currentSquareY,64,64};
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
                SDL_RenderFillRect(renderer, &block);
            } else {
                SDL_Rect block {currentSquareX, currentSquareY,64,64};
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &block);
            }

            // Draw Walls
            if(this->level->wallMap.at(currentTile) == 1){
                SDL_Rect block {currentSquareX, currentSquareY,64,64};
                SDL_RenderCopy(renderer,tmpTexture,NULL,&currentTileDimensions);
              }
            }
            else {
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_Rect block {currentSquareX, currentSquareY,64,64};
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }
    
}

void Game::drawFloor(){
    
}


void Game::render(){
    SDL_RenderSetLogicalSize(renderer, 1088, 704);
    SDL_RenderClear(renderer);

    // Draw map
    //   Draw floor
    //   Draw floor items
    //   Draw walls

    drawMap();
    SDL_DestroyTexture(tmpTexture);
    SDL_FreeSurface(tmpSurface);

    renderPlayer(this->player);
    checkCollisions(player);


    // SDL_SetRenderDrawColor(renderer,255,255,255,255); // set background color to White

    SDL_RenderPresent(renderer);
}

void Game::renderPlayer(Player * player){

    animationHandler->drawSprite(renderer, player);
  

}



void Game::checkCollisions(Player * player){
    bool isColliding = false;
    int playerXMin = floorf(player->playerX);
    int playerXMax = ceil(player->playerX);
    int playerYMin = floorf(player->playerY);
    int playerYMax = ceil(player->playerY);
    if(this->level->wallMap.at(playerYMin*this->level->mapX+playerXMin) == 1){isColliding = true; drawCollisionbox(playerXMin,playerYMin);}
    if(this->level->wallMap.at(playerYMin*this->level->mapX+playerXMax) == 1){isColliding = true; drawCollisionbox(playerXMax,playerYMin);}
    if(this->level->wallMap.at(playerYMax*this->level->mapX+playerXMin) == 1){isColliding = true; drawCollisionbox(playerXMin,playerYMax);}
    if(this->level->wallMap.at(playerYMax*this->level->mapX+playerXMax) == 1){isColliding = true; drawCollisionbox(playerXMax,playerYMax);}
}

// Used for debugging mainly
void Game::drawCollisionbox(int boxX, int boxY){

    float relativeBoxTopLeftX = boxX - player->playerX;
    float relativeBoxTopLeftY = boxY - player->playerY;

    SDL_SetRenderDrawColor(renderer,255,255,0,255); // Yellow
    // Left border
    SDL_Rect block {middleOfScreenX + (int)(relativeBoxTopLeftX*64) , middleOfScreenY + int(relativeBoxTopLeftY*64),3,64}; // Top
    SDL_RenderFillRect(renderer, &block);
     // Right border
    block  = {middleOfScreenX + (int)(relativeBoxTopLeftX*64) + 61 , middleOfScreenY + int(relativeBoxTopLeftY*64),3,64}; // Top
    SDL_RenderFillRect(renderer, &block);
    // Top border
    block  = {middleOfScreenX + (int)(relativeBoxTopLeftX*64) , middleOfScreenY + int(relativeBoxTopLeftY*64),64,3}; // Top
    SDL_RenderFillRect(renderer, &block);
    // Bottom border
    block  = {middleOfScreenX + (int)(relativeBoxTopLeftX*64) , middleOfScreenY + int(relativeBoxTopLeftY*64)+64,64,3}; // Top
    SDL_RenderFillRect(renderer, &block);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}