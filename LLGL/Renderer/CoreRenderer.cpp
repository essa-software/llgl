#include "CoreRenderer.hpp"

#include <LLGL/Core/Matrix.hpp>
#include <LLGL/OpenGL/Shader.hpp>
#include <LLGL/OpenGL/Texture.hpp>
#include <LLGL/OpenGL/Transform.hpp>
#include <LLGL/OpenGL/VAO.hpp>
#include <LLGL/OpenGL/Vertex.hpp>
#include <LLGL/Renderer/StateScope.hpp>
#include <iostream>

namespace llgl {

void CoreRenderer::apply_view(View const& view)
{
    m_view = view;
    opengl::set_viewport(view.viewport());
}

View CoreRenderer::view() const
{
    return m_view;
}

void CoreRenderer::draw_vao(opengl::VAO const& vao, opengl::PrimitiveType primitive_type, DrawState const& state)
{
    StateScope scope(state, m_view);
    vao.draw(state.shader->attribute_mapping(), primitive_type);
}

}
