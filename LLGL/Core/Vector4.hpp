#pragma once

#include "VectorUtils.hpp"

#include <concepts>
#include <ostream>

namespace llgl {

template<class T>
class Vector4 {
public:
    Vector4() = default;

    Vector4(T x_, T y_, T z_, T w_ = 1)
        : x { x_ }
        , y { y_ }
        , z { z_ }
        , w { w_ }
    {
    }

    explicit Vector4(concepts::Vector3 auto other)
        : x { other.x }
        , y { other.y }
        , z { other.z }
    {
    }

    explicit Vector4(concepts::Vector2 auto other)
        : x { other.x }
        , y { other.y }
    {
    }

    Vector4& operator=(concepts::Vector3 auto other)
    {
        if constexpr (std::is_same_v<decltype(&other), decltype(this)>) {
            if (this == &other)
                return *this;
        }
        x = other.x;
        y = other.y;
        z = other.z;
        w = 1;
        return *this;
    }

    Vector4& operator=(concepts::Vector2 auto other)
    {
        x = other.x;
        y = other.y;
        z = 0;
        w = 1;
        return *this;
    }

    T x {}, y {}, z {}, w { 1 };
};

template<class T>
std::ostream& operator<<(std::ostream& out, Vector4<T> const& v)
{
    return out << "[" << v.x << "," << v.y << "," << v.z << "," << v.w << "]";
}

using Vector4i = Vector4<int>;
using Vector4f = Vector4<float>;
using Vector4d = Vector4<double>;

}
