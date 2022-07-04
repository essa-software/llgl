#pragma once

#include "VectorUtils.hpp"

#include <concepts>
#include <ostream>

namespace llgl {

template<class T>
struct UninitializedVector3 {
    UninitializedVector3() = default;

    UninitializedVector3(T x_, T y_, T z_)
        : x { x_ }
        , y { y_ }
        , z { z_ }
    {
    }

    explicit UninitializedVector3(concepts::Vector3 auto other)
        : x { other.x }
        , y { other.y }
        , z { other.z }
    {
    }

    explicit UninitializedVector3(concepts::Vector2 auto other)
        : x { other.x }
        , y { other.y }
        , z { 0 }
    {
    }

    UninitializedVector3& operator=(concepts::Vector3 auto other)
    {
        if constexpr (std::is_same_v<decltype(&other), decltype(this)>) {
            if (this == &other)
                return *this;
        }
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    UninitializedVector3& operator=(concepts::Vector2 auto other)
    {
        x = other.x;
        y = other.y;
        z = 0;
        return *this;
    }

    T x, y, z;
};

template<class T>
class Vector3 {
public:
    Vector3() = default;

    Vector3(T x_, T y_, T z_ = 0)
        : x { x_ }
        , y { y_ }
        , z { z_ }
    {
    }

    explicit Vector3(concepts::Vector3 auto other)
        : x { static_cast<T>(other.x) }
        , y { static_cast<T>(other.y) }
        , z { static_cast<T>(other.z) }
    {
    }

    explicit Vector3(concepts::Vector2 auto other)
        : x { static_cast<T>(other.x) }
        , y { static_cast<T>(other.y) }
        , z { 0 }
    {
    }

    constexpr static Vector3 create_spheric(double lat_radians, double lon_radians, double radius)
    {
        return {
            static_cast<T>(radius * std::cos(lat_radians) * std::sin(lon_radians)),
            static_cast<T>(radius * std::sin(lat_radians) * std::sin(lon_radians)),
            static_cast<T>(radius * std::cos(lon_radians)),
        };
    }

    Vector3& operator=(concepts::Vector3 auto other)
    {
        if constexpr (std::is_same_v<decltype(&other), decltype(this)>) {
            if (this == &other)
                return *this;
        }
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Vector3& operator=(concepts::Vector2 auto other)
    {
        x = other.x;
        y = other.y;
        z = 0;
        return *this;
    }

    T x {}, y {}, z {};
};

template<class T>
std::ostream& operator<<(std::ostream& out, Vector3<T> const& v)
{
    return out << "[" << v.x << "," << v.y << "," << v.z << "]";
}

using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;

}
