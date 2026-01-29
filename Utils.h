#ifndef UTILS_H
#define UTILS_H

#include <SDL_image.h>

class Utils {
public:
    // Static method declarations
    static bool isCollidingAABB(const SDL_Rect& a, const SDL_Rect& b);

    static bool pointInRect(int x, int y, SDL_Rect rect) {
        return (x >= rect.x && x <= rect.x + rect.w &&
                y >= rect.y && y <= rect.y + rect.h);
    }
};

#endif // UTILS_H