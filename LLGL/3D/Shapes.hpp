#pragma once

#include <LLGL/Core/Vertex.hpp>
#include <LLGL/Renderer/Transform.hpp>
#include <vector>

namespace llgl::Shapes {

void add_cube(std::vector<Vertex>& vertices, Transform const& transform = llgl::Transform {});

}
