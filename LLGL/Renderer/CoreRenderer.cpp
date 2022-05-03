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

void CoreRenderer::begin_draw(RendererConfig config)
{
    m_config = std::move(config);
    m_vertexes.clear();
}

void CoreRenderer::add_vertexes(std::span<Vertex const> vertexes)
{
    assert(m_config.primitive_type != opengl::PrimitiveType::Invalid);
    m_vertexes.insert(m_vertexes.end(), vertexes.begin(), vertexes.end());
}

void CoreRenderer::end_draw()
{
    if (m_vertexes.empty())
        return;

    // Shaders are required in core OpenGL
    assert(m_config.shader);

    opengl::VAO vao;
    // Keep these indexes in sync with shader in Shader.cpp!
    vao.load_vertexes(m_config.shader->attribute_mapping(), m_vertexes);
    vao.draw(*this, m_config);
    m_config.primitive_type = opengl::PrimitiveType::Invalid;
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
