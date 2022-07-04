#include "BatchRenderer.hpp"

#include <LLGL/Core/DelayedInit.hpp>
#include <LLGL/OpenGL/VAO.hpp>
#include <LLGL/Renderer/StateScope.hpp>

namespace llgl {

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
    m_commands.push_back({ m_current_primitive_type, std::move(m_current_state), opengl::VAO { m_vertexes } });
    m_vertexes.clear();
}

void BatchRenderer::render(Renderer& renderer, DrawState state) const
{
    for (auto const& command : m_commands) {
        auto this_state = command.state;
        this_state.view_matrix = state.view_matrix;
        renderer.draw_vao(command.vao, command.primitive_type, this_state);
    }
}

}
