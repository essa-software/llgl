#include "VAO.hpp"

#include "Error.hpp"
#include "Extensions.hpp"

#include <LLGL/Core/DelayedInit.hpp>
#include <LLGL/Renderer/Renderer.hpp>

#include <cassert>
#include <iostream>
#include <vector>

namespace llgl::opengl
{

VAO::VAO()
{
    ensure_glew();
}

VAO::VAO(AttributeMapping attribute_mapping, std::span<Vertex const> vertexes)
{
    ensure_glew();
    glGenVertexArrays(1, &m_vertex_array_id);
    handle_error();
    load_vertexes(attribute_mapping, vertexes);
}

VAO::VAO(VAO&& other)
{
    *this = std::move(other);
}

VAO& VAO::operator=(VAO&& other)
{
    if (this == &other)
        return *this;
    m_vertex_array_id = std::exchange(other.m_vertex_array_id, 0);
    m_vertex_buffer_id = std::exchange(other.m_vertex_buffer_id, 0);
    m_size = std::exchange(other.m_size, 0);
    return *this;
}

VAO::~VAO()
{
    if (m_vertex_buffer_id)
    {
        glDeleteBuffers(1, &m_vertex_buffer_id);
        handle_error();
    }
    if (m_vertex_array_id)
    {
        glDeleteVertexArrays(1, &m_vertex_array_id);
        handle_error();
    }
}

void VAO::load_vertexes(AttributeMapping attribute_mapping, std::span<Vertex const> vertexes)
{
    if (m_vertex_array_id == 0)
    {
        glGenVertexArrays(1, &m_vertex_array_id);
        handle_error();
    }
    bind();
    if (!m_vertex_buffer_id)
    {
        glGenBuffers(1, &m_vertex_buffer_id);
        handle_error();
    }
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_id);
    handle_error();
    std::cerr << "VAO: Loading " << vertexes.size() << " vertexes" << std::endl;

    // FIXME: Make this more flexible
    glEnableVertexAttribArray(attribute_mapping.position);
    handle_error();
    glEnableVertexAttribArray(attribute_mapping.color);
    handle_error();
    glEnableVertexAttribArray(attribute_mapping.tex_coord);
    handle_error();
    glEnableVertexAttribArray(attribute_mapping.normal);
    handle_error();
    glBufferData(GL_ARRAY_BUFFER, vertexes.size() * sizeof(Vertex), vertexes.data(), GL_STATIC_DRAW);
    handle_error();
    glVertexAttribPointer(attribute_mapping.position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position)); // x,y
    handle_error();
    glVertexAttribPointer(attribute_mapping.color, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color)); // x,y
    handle_error();
    glVertexAttribPointer(attribute_mapping.tex_coord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord)); // x,y
    handle_error();
    glVertexAttribPointer(attribute_mapping.normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal)); // x,y
    handle_error();

    m_size = vertexes.size();
}

void VAO::bind() const
{
    assert(m_vertex_array_id);
    glBindVertexArray(m_vertex_array_id);
    handle_error();
}

void VAO::draw(PrimitiveType primitive_type) const
{
    bind();
    glDrawArrays(static_cast<GLenum>(primitive_type), 0, m_size);
    handle_error();
}

void VAO::draw(Renderer& renderer, RendererConfig const& config) const
{
    assert(config.shader);
    opengl::ShaderScope scope { *config.shader };

    // TODO: Move it to ShaderScope
    scope.set_uniform("projectionMatrix", renderer.view().matrix());
    scope.set_uniform("modelviewMatrix", config.modelview_matrix);
    DelayedInit<opengl::TextureBinder> binder;
    if (config.texture)
    {
        binder.construct(*config.texture);
        scope.set_uniform("texture", opengl::ShaderScope::CurrentTexture);
        scope.set_uniform("textureSet", true);
    }
    else
        scope.set_uniform("textureSet", false);
    // END TODO

    draw(config.primitive_type);
}

}
