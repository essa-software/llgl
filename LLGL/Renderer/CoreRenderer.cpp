#include "CoreRenderer.hpp"
#include "LLGL/OpenGL/Texture.hpp"

#include <LLGL/Core/Matrix.hpp>
#include <LLGL/OpenGL/Shader.hpp>
#include <LLGL/OpenGL/Transform.hpp>
#include <LLGL/OpenGL/VAO.hpp>
#include <LLGL/OpenGL/Vertex.hpp>
#include <iostream>

namespace llgl
{

void CoreRenderer::begin_draw(opengl::PrimitiveType pt, DrawState state)
{
    m_primitive_type = pt;
    m_state = state;
    m_vertexes.clear();
}

void CoreRenderer::add_vertexes(std::span<Vertex const> vertexes)
{
    assert(m_primitive_type != opengl::PrimitiveType::Invalid);
    m_vertexes.insert(m_vertexes.end(), vertexes.begin(), vertexes.end());
}

void CoreRenderer::end_draw()
{
    if (m_vertexes.empty())
        return;

    // Shaders are required in core OpenGL
    assert(m_state.shader);

    opengl::VAO vao;
    // Keep these indexes in sync with shader in Shader.cpp!
    vao.load_vertexes(m_state.shader->attribute_mapping(), m_vertexes);
    draw_vao(vao, m_primitive_type, m_state);
    m_primitive_type = opengl::PrimitiveType::Invalid;
}

void CoreRenderer::apply_view(View const& view)
{
    m_view = view;
    opengl::set_viewport(view.viewport());
}

View CoreRenderer::view() const
{
    return m_view;
}

}
