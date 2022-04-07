#include "BatchRenderer.hpp"

#include <LLGL/Core/DelayedInit.hpp>
#include <LLGL/OpenGL/VAO.hpp>

namespace llgl
{

void BatchRenderer::begin_draw(RendererConfig config)
{
    m_current_config = std::move(config);
    if(!m_current_config.shader)
        m_current_config.shader = &opengl::shaders::basic_330_core();
    m_vertexes.clear();
}

void BatchRenderer::add_vertexes(std::span<Vertex const> vertexes)
{
    m_vertexes.insert(m_vertexes.end(), vertexes.begin(), vertexes.end());
}

void BatchRenderer::end_draw()
{
    m_commands.emplace_back(std::move(m_current_config), opengl::VAO{m_current_config.shader->attribute_mapping(), m_vertexes});
    m_vertexes.clear();
}

void BatchRenderer::render(Renderer& renderer) const
{
    for(auto const& command : m_commands)
    {
        opengl::ShaderScope scope{*command.config.shader};
        scope.set_uniform("projectionMatrix", renderer.view().matrix());

        {
            DelayedInit<opengl::TextureBinder> binder;
            if(command.config.texture)
                binder.construct(*command.config.texture);
            scope.set_uniform("modelviewMatrix", command.config.modelview_matrix);
            command.vao.draw(command.config.primitive_type);
        };
    }
}

}
