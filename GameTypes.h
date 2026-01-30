#ifndef GAMETYPES_H
#define GAMETYPES_H

enum class MenuType {
    NONE,
    PLAYER_INVENTORY,
    CHEST,
    CRAFTING,
    NPC_DIALOG
};


struct Item {
    std::string name;
    int atlasX; 
    int atlasY;
};

#endif