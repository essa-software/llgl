#include "Mouse.hpp"

#include <SDL2/SDL_mouse.h>

namespace llgl
{

Vector2i mouse_position()
{
    int x;
    int y;
    SDL_GetMouseState(&x, &y);
    return { x, y };
}

}
