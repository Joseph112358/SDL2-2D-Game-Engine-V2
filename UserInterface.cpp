#include "UserInterface.h"
#include <stdio.h>
#include <SDL.h>
#include "Utils.h"

UserInterface::UserInterface(){
        this->isInventoryShown = false;
        this->isInteractButtonShown = false;
        this->activeMenu = MenuType::NONE;


        // 2. Clear all slots to nullptr first (IMPORTANT for safety)
    for(int i = 0; i < 10; i++) {
        chestSlots[i].item = nullptr;

        Item* testItem = new Item{"Test Sword", 0, 16};

        // 4. Put it in the first slot
        this->chestSlots[0].item = testItem;
    }
}

// current screen coords for reference: 1088,704

void UserInterface::drawWindow(SDL_Renderer* renderer, SDL_Color color){
    // Center the window automatically based on a standard 1080p or 720p target
    int screenW = 1088; // Ideally pass these in or use constants
    int screenH = 704;

    // SDL_Rect rect = { (screenW - w) / 2, (screenH - h) / 2, w, h };
    SDL_Rect rect = this->windowRect;

    // Background with transparency
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 200); 
    SDL_RenderFillRect(renderer, &rect);
    
    // Border
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);

}

void UserInterface::handleMouseEvents(SDL_Event& e) {
    int mx, my;
    SDL_GetMouseState(&mx, &my);

    if (e.type == SDL_MOUSEBUTTONDOWN) {
        // 1. Check Title Bar (First 30px of window)
        SDL_Rect titleBar = { windowRect.x, windowRect.y, windowRect.w, 30 };
        if (Utils::pointInRect(mx, my, titleBar)) {
            isDraggingWindow = true;
            dragOffsetX = mx - windowRect.x; // Capture the offset!
            dragOffsetY = my - windowRect.y;
            return;
        }

        // 2. Check Slots
        for (int i = 0; i < 10; i++) {
            if (Utils::pointInRect(mx, my, chestSlots[i].rect) && chestSlots[i].item) {
                draggingItem = chestSlots[i].item;
                chestSlots[i].item = nullptr;
                sourceSlotIndex = i;
                return;
            }
        }
    }

    // UPDATE POSITION DURING MOTION
    if (e.type == SDL_MOUSEMOTION && isDraggingWindow) {
        windowRect.x = mx - dragOffsetX;
        windowRect.y = my - dragOffsetY;
    }

    if (e.type == SDL_MOUSEBUTTONUP) {
        isDraggingWindow = false;

        if (draggingItem) {
            bool droppedInSlot = false;
            for (int i = 0; i < 10; i++) {
                if (Utils::pointInRect(mx, my, chestSlots[i].rect)) {
                    chestSlots[i].item = draggingItem;
                    droppedInSlot = true;
                    break;
                }
            }
            if (!droppedInSlot) {
                chestSlots[sourceSlotIndex].item = draggingItem;
            }
            draggingItem = nullptr;
        }
    }
}


void UserInterface::render(SDL_Renderer* renderer, SDL_Texture* tex) {
    if (activeMenu == MenuType::CHEST) {
        drawWindow(renderer, {40, 40, 40, 255});
        
        int slotsPerRow = 5; // Grid logic so they stay inside the window
        int slotSize = 64;
        int padding = 10;

        for (int i = 0; i < 10; i++) {
            int row = i / slotsPerRow;
            int col = i % slotsPerRow;

            // Slots move with window
            chestSlots[i].rect = { 
                windowRect.x + 20 + (col * (slotSize + padding)), 
                windowRect.y + 50 + (row * (slotSize + padding)), 
                slotSize, 
                slotSize 
            };
            
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_RenderFillRect(renderer, &chestSlots[i].rect);

            if (chestSlots[i].item) {
                SDL_Rect src = { chestSlots[i].item->atlasX, chestSlots[i].item->atlasY, 16, 16 };
                SDL_RenderCopy(renderer, tex, &src, &chestSlots[i].rect);
            }
        }

        if (draggingItem) {
            int mx, my;
            SDL_GetMouseState(&mx, &my);
            SDL_Rect ghostRect = { mx - 32, my - 32, 64, 64 };
            SDL_Rect src = { draggingItem->atlasX, draggingItem->atlasY, 16, 16 };
            SDL_RenderCopy(renderer, tex, &src, &ghostRect);
        }
    }
}


// Temporary fix for prototyping, really need to overhaul how textures are loaded and accessed
void UserInterface::drawInteractButton(SDL_Texture* itemsTexture,SDL_Renderer *renderer){
                SDL_Rect interactButtonAtlas {0, 32, 64, 16};
                SDL_Rect block {420, 600,256,64};
                SDL_RenderCopy(renderer,itemsTexture,&interactButtonAtlas,&block);

}

void UserInterface::drawInventoryMenu(SDL_Renderer * renderer){
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_Rect block { 64, 64,64,64};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128); // Set to red
    SDL_RenderFillRect(renderer, &block);
}

void UserInterface::toggleInventoryShown(){
    isInventoryShown = !isInventoryShown;
}
