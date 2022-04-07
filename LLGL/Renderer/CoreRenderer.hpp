#pragma once

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
    virtual void begin_draw(RendererConfig) override;
    virtual void add_vertexes(std::span<Vertex const> vertexes) override;
    virtual void end_draw() override;
    virtual void apply_view(View const&) override;
    virtual View view() const override;

private:
    RendererConfig m_config {};
    std::vector<Vertex> m_vertexes;
    View m_view;
};

}
