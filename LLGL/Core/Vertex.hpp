#pragma once

#include <LLGL/Core/Color.hpp>
#include <LLGL/Core/Vector2.hpp>
#include <LLGL/Core/Vector3.hpp>

namespace llgl
{

struct Vertex
{
    Vector3f position;
    Colorf color;
    Vector2f tex_coord;
    Vector3f normal;
};

}