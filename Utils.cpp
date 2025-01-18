#include "Utils.h"

bool Utils::isCollidingAABB(const SDL_Rect& a, const SDL_Rect& b){
    return !(a.x + a.w < b.x || // `a` is to the left of `b`
             a.x > b.x + b.w || // `a` is to the right of `b`
             a.y + a.h < b.y || // `a` is above `b`
             a.y > b.y + b.h);  // `a` is below `b`
}