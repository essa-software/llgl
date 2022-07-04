#pragma once

#include <LLGL/Core/Vertex.hpp>
#include <LLGL/Renderer/Transform.hpp>
#include <vector>

namespace llgl::Shapes {

struct CubeProperties {
    Vector3f position {};
    Vector3f dimensions { 1, 1, 1 };
    Transform transform {}; // Is applied after position+dimensions
    Color color = Colors::white;
};

void add_cube(std::vector<Vertex>& vertices, CubeProperties properties = {});

}
