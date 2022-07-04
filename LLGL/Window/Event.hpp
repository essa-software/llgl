#pragma once

#include <LLGL/Core/Vector2.hpp>
#include <LLGL/Window/Keyboard.hpp>
#include <LLGL/Window/Mouse.hpp>

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
        MouseButtonPress,
        MouseButtonRelease,
    } type {};

    struct ResizeEvent
    {
        UninitializedVector2<int> size;
    };
    struct KeyPressEvent
    {
        KeyCode keycode;
        bool shift;
        bool ctrl;
        bool alt;
        bool meta;
    };
    struct MouseMoveEvent
    {
        UninitializedVector2<int> position;
        UninitializedVector2<int> relative;
    };
    struct MouseButtonEvent
    {
        UninitializedVector2<int> position;
        MouseButton button;
    };
    union
    {
        ResizeEvent resize;
        KeyPressEvent key;
        MouseMoveEvent mouse_move;
        MouseButtonEvent mouse_button;
    };
};

}
