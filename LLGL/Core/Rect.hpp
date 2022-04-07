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

    Vector2<T> position() const { return {left, top}; }
    Vector2<T> size() const { return {width, height}; }
};

using Recti = Rect<int>;
using Rectf = Rect<float>;
using Rectd = Rect<double>;

}
