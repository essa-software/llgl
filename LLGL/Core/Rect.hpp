#pragma once

#include <concepts>

#include "Vector2.hpp"

namespace llgl
{

template<class T>
class Rect
{
public:
    T left {};
    T top {};
    T width {};
    T height {};

    Vector2<T> position() const { return { left, top }; }
    Vector2<T> size() const { return { width, height }; }

    bool contains(Vector2<T> pos) const
    {
        return pos.x >= left && pos.x <= left + width && pos.y >= top && pos.y <= top + height;
    }
};

using Recti = Rect<int>;
using Rectf = Rect<float>;
using Rectd = Rect<double>;

}
