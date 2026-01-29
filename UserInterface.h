#pragma once
#include <vector>
#include <iostream>
#include <SDL_image.h>
#include "GameTypes.h"
#include <queue>

// Items code
        struct Item {
        std::string name;
        int atlasX; // Where it is on your miscTexture
        int atlasY;
        };

        struct Slot {
        SDL_Rect rect;   // Where the slot is drawn on screen
        Item* item = nullptr; 
        };

class UserInterface {
    public:
        SDL_Rect windowRect = { 200, 200, 500, 400 }; // Default position
        bool isDraggingWindow = false;
        int dragOffsetX = 0;
        int dragOffsetY = 0;
        void handleMouseEvents(SDL_Event& e);

        MenuType activeMenu = MenuType::NONE;
        UserInterface();
        bool isInventoryShown;
        bool isInteractButtonShown;

        // New 
        // A generic function to draw a centered window
        void drawWindow(SDL_Renderer* renderer, SDL_Color color);

        // The main render call
        void render(SDL_Renderer* renderer, SDL_Texture* uiTexture);


        // Some of these can / will be migrated / deprecated
        void drawInteractButton(SDL_Texture* itemsTexture,SDL_Renderer *renderer);
        void toggleInventoryShown();
        void drawInventoryMenu(SDL_Renderer * renderer);

        // New Drag & Drop members
        Slot chestSlots[10];      // 10 slots for the chest
        Item* draggingItem = nullptr; 
        int sourceSlotIndex = -1; // Where the item came from

        void initChestSlots();    // Setup the grid
        // ...

};
