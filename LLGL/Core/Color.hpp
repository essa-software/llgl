#pragma once

#include <cstdint>

namespace llgl
{

class Color
{
public:
    uint8_t r {}, g {}, b {}, a {255};
};

class Colors
{
public:
    static constexpr Color white {255, 255, 255};
    static constexpr Color black {};
    static constexpr Color red {255, 0, 0};
    static constexpr Color green {0, 255, 0};
    static constexpr Color blue {0, 0, 255};
};

struct Colorf
{
    Colorf() = default;
    Colorf(float r_, float g_, float b_, float a_ = 1)
    : r(r_), g(g_), b(b_), a(a_) {}

    Colorf(Color const& color)
    : r(color.r / 255.f), g(color.g / 255.f), b(color.b / 255.f), a(color.a / 255.f) {}

    float r,g,b,a;
};

}
