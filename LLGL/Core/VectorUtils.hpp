#pragma once

#include "Concepts.hpp"

#include <cmath>

namespace llgl::vector
{

using llgl::concepts::Vector2;
using llgl::concepts::Vector3;

auto length_squared(Vector2 auto vector)
{
    return vector.x * vector.x + vector.y * vector.y;
}

auto length(Vector2 auto vector)
{
    return std::sqrt(length_squared(vector));
}

auto distance_squared(Vector2 auto first, Vector2 auto second)
{
    return length(second - first);
}

auto distance(Vector2 auto first, Vector2 auto second)
{
    return std::sqrt(distance_squared(first, second));
}

auto angle(Vector2 auto vector)
{
    return std::atan2(vector.y, vector.x);
}

auto perpendicular(Vector2 auto vector) -> decltype(vector)
{
    return {-vector.y, vector.x};
}

auto dot_product(Vector2 auto first, Vector2 auto second)
{
    return first.x * second.y - first.y * second.x;
}

auto cross_product(Vector3 auto first, Vector3 auto second)
{
    auto x = first.y * second.z - first.z * second.y;
    auto y = first.z * second.x - first.x * second.z;
    auto z = first.x * second.y - first.y * second.x;
    return decltype(first){x, y, z};
}

bool is_normalized(Vector2 auto vec)
{
    return length_squared(vec) == 1;
}

auto normalize(Vector2 auto vec) -> decltype(vec)
{
    if(is_normalized(vec))
        return vec;
    auto vec_length = std::sqrt(length(vec));
    return {vec.x / vec_length, vec.y / vec_length};
}

auto mirror(Vector2 auto vec, Vector2 auto axis)
{
    return vec - (decltype(vec.x))2 * dot_product(vec, normalize(axis)) * axis;
}

}

namespace {

using llgl::concepts::Vector2;
using llgl::concepts::Vector3;

auto operator+(Vector2 auto first, Vector2 auto second) { return decltype(first){first.x + second.x, first.y + second.y}; }
auto operator-(Vector2 auto first, Vector2 auto second) { return decltype(first){first.x - second.x, first.y - second.y}; }
auto operator*(Vector2 auto first, auto scalar) { return decltype(first){first.x * scalar, first.y * scalar}; }
auto operator/(Vector2 auto first, auto scalar) { return decltype(first){first.x / scalar, first.y / scalar}; }
auto operator==(Vector2 auto first, Vector2 auto second) { return first.x == second.x && first.y == second.y; }
auto operator!=(Vector2 auto first, Vector2 auto second) { return !(first == second); }

auto operator+(Vector3 auto first, Vector3 auto second) { return decltype(first){first.x + second.x, first.y + second.y, first.z + second.z}; }
auto operator-(Vector3 auto first, Vector3 auto second) { return decltype(first){first.x - second.x, first.y - second.y, first.z - second.z}; }
auto operator*(Vector3 auto first, auto scalar) { return decltype(first){first.x * scalar, first.y * scalar, first.z * scalar}; }
auto operator/(Vector3 auto first, auto scalar) { return decltype(first){first.x / scalar, first.y / scalar, first.z / scalar}; }
auto operator==(Vector3 auto first, Vector3 auto second) { return first.x == second.x && first.y == second.y && first.z == second.z; }
auto operator!=(Vector3 auto first, Vector3 auto second) { return !(first == second); }

}
