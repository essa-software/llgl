#include "BatchRenderer.hpp"

#include <LLGL/Core/DelayedInit.hpp>
#include <LLGL/OpenGL/VAO.hpp>

namespace llgl
{

void BatchRenderer::begin_draw(RendererConfig config)
{
    m_current_config = std::move(config);
    m_current_config.shader = nullptr;
    m_vertexes.clear();
}

void BatchRenderer::add_vertexes(std::span<Vertex const> vertexes)
{
    m_vertexes.insert(m_vertexes.end(), vertexes.begin(), vertexes.end());
}

void BatchRenderer::end_draw()
{
    m_commands.emplace_back(std::move(m_current_config), opengl::VAO { m_current_config.shader->attribute_mapping(), m_vertexes });
    m_vertexes.clear();
}

void BatchRenderer::render(Renderer& renderer) const
{
    for (auto const& command : m_commands)
    {
        opengl::ShaderScope scope { *command.config.shader };
        // TODO: Move it to ShaderScope
        scope.set_uniform("projectionMatrix", renderer.view().matrix());

        {
            DelayedInit<opengl::TextureBinder> binder;
            if (command.config.texture)
                binder.construct(*command.config.texture);
            scope.set_uniform("modelviewMatrix", command.config.modelview_matrix);
            // END TODO
            command.vao.draw(command.config.primitive_type);
        };
    }
}

}
