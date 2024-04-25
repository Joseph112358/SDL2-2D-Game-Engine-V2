#ifndef Game_hpp
#define Game_hpp

#include <SDL.h>
#include <stdio.h>
#include<vector>
#include "Level.h"
#include "Player.h"
#include "Entity.h"
class Game {
    public:
        Game();
        ~Game();

        Level * level;

        Player * player;
        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

        // Maybe take in user inputs
        void handleEvents();
        void update();
        void render();

        void drawMap();
        void drawWalls();
        void drawFloor();
        void drawEntity(Entity * entity);
    
        void renderPlayer(Player * player);
        void checkCollisions(Player * player);
        void drawCollisionbox(int boxX, int boxY);
        void clean();


        bool running() {return isRunning;}

    private:
        bool isRunning;
        void handleKeyboardInput(SDL_Event e);
        SDL_Window *window;
        SDL_Renderer *renderer; 
};

#endif /* Game_h*/