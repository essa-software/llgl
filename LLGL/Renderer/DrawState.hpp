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
    Matrix4x4f model_matrix = Matrix4x4f::identity();
    Matrix4x4f view_matrix = Matrix4x4f::identity();
};

}
