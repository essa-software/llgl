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
        MouseMove,
    } type {};

    struct ResizeEvent
    {
        UninitializedVector2<int> size;
    };
    struct KeyPressEvent
    {
        KeyCode keycode;
    };
    struct MouseMoveEvent
    {
        UninitializedVector2<int> position;
        UninitializedVector2<int> relative;
    };
    union
    {
        ResizeEvent resize;
        KeyPressEvent key;
        MouseMoveEvent mouse_move;
    };
};

}
