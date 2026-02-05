#ifndef GAMETYPES_H
#define GAMETYPES_H


struct Item {
    std::string name;
    int atlasX; 
    int atlasY;
};

struct Inventory {
    Item* slots[10] = { nullptr };
};

// TODO: This is not designed really, so work this out.
enum class MenuType {
    NONE,
    PLAYER_INVENTORY,
    CHEST,
    CRAFTING,
    NPC_DIALOG
};

enum class InteractionType {
    None,
    OpenContainer
};

struct InteractionResult {
    InteractionType type = InteractionType::None;
    
    union {
        Inventory* container;
    } data;

    static InteractionResult Open(Inventory* inv) {
        InteractionResult r;
        r.type = InteractionType::OpenContainer;
        r.data.container = inv;
        return r;
    }

    static InteractionResult Empty() {
        return { InteractionType::None };
    }
};

#endif