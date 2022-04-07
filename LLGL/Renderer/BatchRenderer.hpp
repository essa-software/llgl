#pragma once

#include "LLGL/OpenGL/VAO.hpp"
#include "Renderer.hpp"
#include "Renderable.hpp"

#include <vector>

namespace llgl
{

// Stores vertexes into an internal array. Doesn't actually render anything
class BatchRenderer : public Renderer, public Renderable
{
public:
    BatchRenderer(Window& window)
    : Renderer(window) {}

    virtual void begin_draw(RendererConfig) override;
    virtual void add_vertexes(std::span<Vertex const> vertexes) override;
    virtual void end_draw() override;
    virtual void apply_view(View const&) override {}
    virtual void render(Renderer&) const override;
    virtual View view() const override { return {}; } // TODO

private:
    RendererConfig m_current_config;
    std::vector<Vertex> m_vertexes;

    struct Command
    {
        RendererConfig config;
        opengl::VAO vao;
    };
    std::vector<Command> m_commands;
};

}

