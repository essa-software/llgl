#pragma once

#include "Shader.hpp"
#include "Vertex.hpp"

#include <LLGL/Core/Vertex.hpp>

#include <span>

namespace llgl::opengl
{

class VAO
{
public:
    VAO();
    explicit VAO(AttributeMapping, std::span<Vertex const> vertexes);
    VAO(VAO const&) = delete;
    VAO& operator=(VAO const&) = delete;
    VAO(VAO&&);
    VAO& operator=(VAO&&);
    ~VAO();

    void load_vertexes(AttributeMapping, std::span<Vertex const> vertexes);

    unsigned vertex_array_id() const { return m_vertex_array_id; }
    unsigned vertex_buffer_id() const { return m_vertex_buffer_id; }

    void bind() const;
    void draw(PrimitiveType) const;

private:
    unsigned m_vertex_array_id {};
    unsigned m_vertex_buffer_id {};
    size_t m_size {};
};

}
