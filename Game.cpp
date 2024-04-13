#include "Game.h"
#include <iostream>
#include <vector>
#include "Level.h"
#include "Player.h"
#include <cmath>

int middleOfScreenX = 512; int middleOfScreenY = 320;

Game::Game(){
    // Maybe load map

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
        case SDL_KEYDOWN:
            handleKeyboardInput(event);
        default:
            break;
    }

}

void Game::handleKeyboardInput(SDL_Event e){
      switch(e.key.keysym.sym){
        case SDLK_RIGHT:
            this->player->playerX += 0.25;
            break;
        case SDLK_LEFT:
            this->player->playerX -= 0.25;
            break;
        case SDLK_UP:
            this->player->playerY -= 0.25;
            break;
        case SDLK_DOWN:
            this->player->playerY += 0.25;
            break;
        case SDLK_BACKSPACE:
            std::cout << "Backspace\n";
        default:
            break;
      }

}

void Game::update(){

}

void Game::render(){
    SDL_RenderClear(renderer);

    // Maybe something like Player::drawPlayer(Renderer * renderer)
    // And Level::drawMap(Renderer * renderer)

    // for(int i = 0; i < this->level->mapX; i++){
    //     for(int j = 0; j < this->level->mapY; j++){
    //         int currentSquareX =  (i *64); // change var name, maybe tileScreenCoords?
    //         int currentSquareY =  (j *64);
    //         // Code for working out tile
    //         int currentTileX = i;
    //         int currentTileY = j;
    //         int currentTile = currentTileY*this->level->mapX+currentTileX;

    //           if(this->level->floorMap.at(currentTile) == 1){
    //             // std:: cout << "Here" << std::endl;
    //             SDL_SetRenderDrawColor(renderer,65,90,90,255);
    //             SDL_Rect block {currentSquareX, currentSquareY,64,64};
    //             SDL_RenderFillRect(renderer, &block);
    //           }
    //     }
    // }



    // Because the player can move by less than 1 tile (0.25 a tile to be precise), we have to find
    // The offset when drawing each tile. The maths is a little complicated but this works

    // This code does not work yet
    int integerPart = static_cast<int>(player->playerX);
    float playerXOffset = player->playerX - integerPart;
    integerPart = static_cast<int>(player->playerY);
    float playerYOffset = player->playerY - integerPart;
    

    // mayeb do floats?
    for(int i = -8; i < 8; i++){
        for(int j = -5; j < 5; j++){
            int currentSquareX = middleOfScreenX + (i *64) - (playerXOffset * 64)  ; // change var name, maybe tileScreenCoords?
            int currentSquareY = middleOfScreenY + (j *64) - (playerYOffset * 64);
            int currentTileX = this->player->playerX+i;
            int currentTileY = this->player->playerY+j;
            int currentTile = currentTileY*this->level->mapX+currentTileX;
            SDL_Rect currentTileDimensions {currentSquareX, currentSquareY,64,64};


            bool inMap = true;
            if(currentTileX > this->level->mapX -1 || currentTileX < 0 || currentTileY > this->level->mapY -1 || currentTileY < 0) inMap = false;
       
            if(inMap){
            if(this->level->floorMap.at(currentTile) == 1){
                SDL_SetRenderDrawColor(renderer,65,90,90,255);
                SDL_Rect block {currentSquareX, currentSquareY,64,64};
                SDL_RenderFillRect(renderer, &block);
              }
            }
            else {
                SDL_SetRenderDrawColor(renderer,0,0,0,255);
                SDL_Rect block {currentSquareX, currentSquareY,64,64};
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }

    renderPlayer();
    checkCollisions(player);

    SDL_SetRenderDrawColor(renderer,255,255,255,255); // set background color to White

    SDL_RenderPresent(renderer);
}

void Game::renderPlayer(){
    //  SDL_SetRenderDrawColor(renderer,0,90,90,255);
    // SDL_Rect block {(int)(this->player->playerX*64),(int)(this->player->playerY*64),64,64};
    // SDL_RenderFillRect(renderer, &block);
    SDL_SetRenderDrawColor(renderer,0,90,90,255);
    SDL_Rect block {middleOfScreenX,middleOfScreenY,64,64};
    SDL_RenderFillRect(renderer, &block);
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
    block  = {middleOfScreenX + (int)(relativeBoxTopLeftX*64) + 64 , middleOfScreenY + int(relativeBoxTopLeftY*64),3,64}; // Top
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