#pragma once

#include <string>

#include <SDL2/SDL_keyboard.h>

namespace llgl
{

#define ENUMERATE_KEYBOARD_KEYCODES(K) \
    K(A, SDLK_a)                       \
    K(D, SDLK_d)                       \
    K(S, SDLK_s)                       \
    K(W, SDLK_w)                       \
    K(Space, SDLK_SPACE)

enum class KeyCode
{
#define __ENUMERATE_KEY(key, value) key = value,
    ENUMERATE_KEYBOARD_KEYCODES(__ENUMERATE_KEY)
#undef __ENUMERATE_KEY
};

constexpr std::string_view to_string(KeyCode key)
{
    switch (key)
    {
#define __ENUMERATE_KEY(key, value) \
    case KeyCode::key:              \
        return #key;
        ENUMERATE_KEYBOARD_KEYCODES(__ENUMERATE_KEY)
#undef __ENUMERATE_KEY
    }
    return "Unknown";
}

}
