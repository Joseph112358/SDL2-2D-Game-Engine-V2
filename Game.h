#ifndef Game_hpp
#define Game_hpp

#include <SDL.h>
#include <stdio.h>
#include<vector>
#include "Level.h"
#include "Player.h"
#include "entities/Entity.h"
#include "entities/EntityFactory.h"
#include "UserInterface.h"
#include "Sprite.h"
#include <list>

class Game {
    public:
        Game();
        ~Game();

        Level * level;

        Player * player;

        UserInterface * userInterface;

        EntityFactory * entityFactory;

        std::vector<Entity *> entities;

        std::list<int> interactablesList;

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

        // Main core functions (will be public to main)
        void handleEvents();
        void update();
        void render();

        void drawMap();
        void drawWalls();
        void drawFloor();
        void drawEntity(Entity * entity);
        void drawEntities(std::vector<Entity*> entities);
        void createNewEntity(int x_pos, int y_pos);
    
        void renderPlayer(Player * player);
        void checkCollisions(std::pair<int,int> coords);

        void drawCollisionbox(int boxX, int boxY);
        void drawCollisionBox(int boxX, int boxY, int width, int height);
        void drawTileBox(int tileIndex);
        void clean();

        // Helper functions
        int coordsToArrayInt(std::pair<int,int> coords);
        std::pair<int,int> arrayIntToPair(int arrayLocation);
        // End of helper functions
        bool running() {return isRunning;}
        bool inRange( std::pair<int,int> playerPoint, std::pair<int,int> itemPoint);

    private:
        bool isRunning;
        void handleKeyboardInput(SDL_Event e);
        void handleKeyInput(SDL_Event e);
        SDL_Window *window;
        SDL_Renderer *renderer; 
};

#endif /* Game_h*/