#ifndef UTILS_H
#define UTILS_H

#include <SDL_image.h>

class Utils {
public:
    // Static method declarations
    static bool isCollidingAABB(const SDL_Rect& a, const SDL_Rect& b);
};

#endif // UTILS_H