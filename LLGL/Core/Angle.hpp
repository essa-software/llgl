#pragma once

#include <cmath>

namespace llgl
{

template<class T>
constexpr T degrees_in_radian = 180 / M_PI;

constexpr auto rad_to_deg(auto radians) {
    return radians * degrees_in_radian<decltype(radians)>;
}

constexpr auto deg_to_rad(auto radians) {
    return radians / degrees_in_radian<decltype(radians)>;
}

}
