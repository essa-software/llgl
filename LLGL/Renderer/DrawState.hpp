#pragma once

#include <LLGL/Core/Matrix.hpp>

namespace llgl
{

namespace opengl
{

class Shader;
class Texture;

}

struct DrawState
{
    opengl::Shader* shader = nullptr;
    opengl::Texture* texture = nullptr;
    Matrix4x4f modelview_matrix = Matrix4x4f::identity();
};

}
