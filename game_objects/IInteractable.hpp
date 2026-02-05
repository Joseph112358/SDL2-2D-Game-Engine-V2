#include <iostream>
#include <string>
#include "./../GameTypes.h"

class UserInterface; // this is temp probs

#pragma once
class IInteractable {
    public:
        virtual ~IInteractable() = default;

        virtual InteractionResult onInteract() = 0;

        virtual MenuType getAssociatedMenu() { return MenuType::NONE; }

        virtual int getAtlasX() const = 0;

        virtual std::string getInteractPrompt() const {return "Interact";}
};