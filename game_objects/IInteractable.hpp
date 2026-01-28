#include <iostream>
#include <string>
#include "./../GameTypes.h"

#pragma once
class IInteractable {
    public:
        virtual ~IInteractable() = default;

        virtual void onInteract() = 0;

        virtual MenuType getAssociatedMenu() { return MenuType::NONE; }

        virtual int getAtlasX() const = 0;

        virtual std::string getInteractPrompt() const {return "Interact";}
};