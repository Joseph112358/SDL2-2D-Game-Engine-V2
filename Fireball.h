#include <SDL_image.h>
#include "Entity.h"

class Fireball: public Entity {
    public:
        Fireball(int x, int y);
        void update();
        // bool isColliding()
        void destroy();
};