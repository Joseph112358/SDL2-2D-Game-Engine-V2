#include "Game.h"
#include <iostream>
#include <vector>
#include "Level.h"
#include "Player.h"
#include <cmath>
#include <SDL_image.h>
#include <thread>
int middleOfScreenX = 512; int middleOfScreenY = 320;
SDL_Surface* tmpSurface = nullptr;
SDL_Texture* tmpTexture = nullptr;

auto lastInputTime = std::chrono::high_resolution_clock::now();
bool playerIdle = false;


int animationFrame = 0;

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
    auto currentTime = std::chrono::high_resolution_clock::now();
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            handleKeyboardInput(event);
            lastInputTime = std::chrono::high_resolution_clock::now();
            playerIdle = false;
        default:
          auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastInputTime);
          if(elapsed.count() > 500){
                playerIdle = true;
          }
          break;
    }

}

void Game::handleKeyboardInput(SDL_Event e){
      switch(e.key.keysym.sym){
        case SDLK_RIGHT:
            this->player->playerX += 0.25;
            player->direction = 90;
            animationFrame == 6 ? animationFrame = 1 : animationFrame++;
            break;
        case SDLK_LEFT:
            this->player->playerX -= 0.25;
            animationFrame == 6 ? animationFrame = 1 : animationFrame++;
            player->direction = 270;
            break;
        case SDLK_UP:
            this->player->playerY -= 0.25;
            player->direction = 0;
            animationFrame == 6 ? animationFrame = 1 : animationFrame++;
            break;
        case SDLK_DOWN:
            this->player->playerY += 0.25;
            player->direction = 180;
            animationFrame == 6 ? animationFrame = 1 : animationFrame++;
            break;
        case SDLK_BACKSPACE:
            std::cout << "Backspace\n";
        default:
            break;
      }

}

// Actually use this
void Game::update(){

}

void Game::render(){
    SDL_RenderSetLogicalSize(renderer, 1088, 704);
    SDL_RenderClear(renderer);

    // Maybe something like Player::drawPlayer(Renderer * renderer)
    // And Level::drawMap(Renderer * renderer)

    // Because the player can move by less than 1 tile (0.25 a tile to be precise), we have to find
    // The offset when drawing each tile. The maths is a little complicated but this works
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
            if(this->level->floorMap.at(currentTile) == 1){
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
    SDL_DestroyTexture(tmpTexture);
    SDL_FreeSurface(tmpSurface);

    renderPlayer(this->player);
    checkCollisions(player);


    SDL_SetRenderDrawColor(renderer,255,255,255,255); // set background color to White

    SDL_RenderPresent(renderer);
}

void Game::renderPlayer(Player * player){
    tmpSurface = IMG_Load("res/player-sprite-v1.png");
    tmpTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    // Should / could be moved to function or class / handler?
    int atlasYPos = 0;
    switch (player->direction){
        case 90: // do right animation
            atlasYPos = 0;
            break;
        case 270: // Do left animation
            atlasYPos = 1;
            break;
        case 0:
            atlasYPos = 2;
            break;
        case 180:
            atlasYPos = 3;
            break;
        default:
            break;
    }
    if(playerIdle) animationFrame = 0, atlasYPos = 0;
    SDL_Rect playerAtlasCoords {animationFrame * 32, atlasYPos * 32, 32, 32};

    SDL_Rect block {middleOfScreenX,middleOfScreenY,64,64};
    SDL_RenderCopy(renderer,tmpTexture,&playerAtlasCoords,&block);

    SDL_DestroyTexture(tmpTexture);
    SDL_FreeSurface(tmpSurface);

}



void Game::checkCollisions(Player * player){
    bool isColliding = false;
    int playerXMin = floorf(player->playerX);
    int playerXMax = ceil(player->playerX);
    int playerYMin = floorf(player->playerY);
    int playerYMax = ceil(player->playerY);
    if(this->level->floorMap.at(playerYMin*this->level->mapX+playerXMin) == 1){isColliding = true; drawCollisionbox(playerXMin,playerYMin);}
    if(this->level->floorMap.at(playerYMin*this->level->mapX+playerXMax) == 1){isColliding = true; drawCollisionbox(playerXMax,playerYMin);}
    if(this->level->floorMap.at(playerYMax*this->level->mapX+playerXMin) == 1){isColliding = true; drawCollisionbox(playerXMin,playerYMax);}
    if(this->level->floorMap.at(playerYMax*this->level->mapX+playerXMax) == 1){isColliding = true; drawCollisionbox(playerXMax,playerYMax);}
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