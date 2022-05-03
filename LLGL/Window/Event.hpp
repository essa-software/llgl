#pragma once

#include <LLGL/Core/Vector2.hpp>
#include <LLGL/Window/Keyboard.hpp>

namespace llgl
{

class Event
{
public:
    enum class Type
    {
        Unknown,
        Resize,
        KeyPress,
        KeyRelease,
    } type {};

    struct ResizeEvent
    {
        UninitializedVector2<int> size;
    };
    struct KeyPress
    {
        KeyCode keycode;
    };
    union
    {
        ResizeEvent resize;
        KeyPress key;
    };
};

}
