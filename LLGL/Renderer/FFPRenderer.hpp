#pragma once

#include "Renderer.hpp"

namespace llgl
{

// Uses fixed pipeline; is just to make something working and
// will be removed if I write new opengl 3 (core) compatible renderer
class FFPRenderer : public Renderer
{
public:
    FFPRenderer(Window& window)
    : Renderer(window) {}

    virtual void begin_draw(opengl::PrimitiveType, DrawState) override;
    virtual void add_vertexes(std::span<Vertex const> vertexes) override;
    virtual void end_draw() override;
    virtual void apply_view(View const&) override;
    virtual View view() const override { return {}; } // TODO
};

}
