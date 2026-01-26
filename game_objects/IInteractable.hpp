#include <iostream>
#include <string>

#pragma once
class IInteractable {
    public:
        virtual ~IInteractable() = default;

        virtual void onInteract() = 0;

        virtual int getAtlasX() const = 0;

        virtual std::string getInteractPrompt() const {return "Interact";}
};