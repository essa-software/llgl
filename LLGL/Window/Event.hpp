#pragma once

#include <LLGL/Core/Vector2.hpp>

namespace llgl
{

class Event
{
public:
    enum class Type
    {
        Unknown,
        Resize
    } type {};

    struct ResizeEvent { UninitializedVector2<int> size; };
    union
    {
        ResizeEvent resize;
    };
};

}
