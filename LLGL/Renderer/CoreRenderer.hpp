#pragma once

#include "LLGL/OpenGL/Vertex.hpp"
#include "Renderer.hpp"

#include <vector>

namespace llgl
{

// Uses programmable pipeline, used for OpenGL 3.2+
class CoreRenderer : public Renderer
{
public:
    CoreRenderer(Window& window)
    : Renderer(window) {}

    virtual void apply_view(View const&) override;
    virtual View view() const override;
    virtual void draw_vao(opengl::VAO const&, opengl::PrimitiveType, DrawState const&) override;

private:
    opengl::PrimitiveType m_primitive_type = opengl::PrimitiveType::Invalid;
    DrawState m_state;
    std::vector<Vertex> m_vertexes;
    View m_view;
};

}
