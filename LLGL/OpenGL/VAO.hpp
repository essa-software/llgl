#pragma once

#include "Shader.hpp"
#include "Vertex.hpp"

#include <LLGL/Core/Vertex.hpp>

#include <optional>
#include <span>

namespace llgl::opengl {

class VAO {
public:
    enum class Usage {
        StaticDraw,
        DynamicDraw
    };

    VAO();
    explicit VAO(std::span<Vertex const> vertexes, Usage usage = Usage::StaticDraw);
    VAO(VAO const&) = delete;
    VAO& operator=(VAO const&) = delete;
    VAO(VAO&&);
    VAO& operator=(VAO&&);
    ~VAO();

    void load_vertexes(std::span<Vertex const> vertexes, Usage usage = Usage::StaticDraw);

    unsigned vertex_array_id() const { return m_vertex_array_id; }
    unsigned vertex_buffer_id() const { return m_vertex_buffer_id; }

    void bind() const;
    void draw(AttributeMapping, PrimitiveType) const;
    void draw_indexed(AttributeMapping, PrimitiveType, std::span<unsigned const> indices) const;

private:
    void bind_with_attributes(AttributeMapping) const;

    unsigned m_vertex_array_id {};
    unsigned m_vertex_buffer_id {};
    size_t m_size {};
    mutable std::optional<AttributeMapping> m_attribute_mapping;
};

}
