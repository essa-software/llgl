#include "BatchRenderer.hpp"

#include <LLGL/Core/DelayedInit.hpp>
#include <LLGL/OpenGL/VAO.hpp>
#include <LLGL/Renderer/StateScope.hpp>

namespace llgl
{

void BatchRenderer::begin_draw(opengl::PrimitiveType pt, DrawState state)
{
    m_current_primitive_type = pt;
    m_current_state = std::move(state);
    assert(m_current_state.shader);
    m_vertexes.clear();
}

void BatchRenderer::add_vertexes(std::span<Vertex const> vertexes)
{
    m_vertexes.insert(m_vertexes.end(), vertexes.begin(), vertexes.end());
}

void BatchRenderer::end_draw()
{
    m_commands.emplace_back(m_current_primitive_type, std::move(m_current_state), opengl::VAO { m_current_state.shader->attribute_mapping(), m_vertexes });
    m_vertexes.clear();
}

void BatchRenderer::render(Renderer& renderer, DrawState) const
{
    // TODO: Use given RendererConfig somehow (combine transforms etc).
    for (auto const& command : m_commands)
        renderer.draw_vao(command.vao, command.primitive_type, command.state);
}

}
