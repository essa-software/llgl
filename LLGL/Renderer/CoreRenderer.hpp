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

    // This is for compatibility; should not be used
    virtual void begin_draw(opengl::PrimitiveType, DrawState) override;
    virtual void add_vertexes(std::span<Vertex const> vertexes) override;
    virtual void end_draw() override;
    virtual void apply_view(View const&) override;
    virtual View view() const override;

private:
    opengl::PrimitiveType m_primitive_type = opengl::PrimitiveType::Invalid;
    DrawState m_state;
    std::vector<Vertex> m_vertexes;
    View m_view;
};

}
