#pragma once

#include "DrawState.hpp"
#include <LLGL/Core/Vertex.hpp>
#include <LLGL/OpenGL/Texture.hpp>
#include <LLGL/OpenGL/VAO.hpp>
#include <LLGL/OpenGL/Vertex.hpp>
#include <LLGL/OpenGL/View.hpp>
#include <span>

namespace llgl
{

class Renderable;
class Window;

class Renderer
{
public:
    Renderer(Window& window)
        : m_window(window)
    {
    }

    virtual void begin_draw(opengl::PrimitiveType, DrawState = {}) = 0;
    virtual void add_vertexes(std::span<Vertex const> vertexes) = 0;
    void add_vertexes(std::initializer_list<Vertex> vertexes)
    {
        add_vertexes(std::span { vertexes });
    }
    virtual void end_draw() = 0;
    virtual void apply_view(View const&) = 0;
    virtual View view() const = 0;

    void render_object(Renderable const&, DrawState = {});
    void draw_vao(opengl::VAO const&, opengl::PrimitiveType, DrawState const&);
    void add_triangle(Vertex _1, Vertex _2, Vertex _3);

protected:
    Window& m_window;
};

class DrawScope
{
public:
    DrawScope(Renderer& renderer, opengl::PrimitiveType pt, DrawState state = {})
        : m_renderer(renderer)
    {
        renderer.begin_draw(pt, std::move(state));
    }

    ~DrawScope() { m_renderer.end_draw(); }

    Renderer& renderer() { return m_renderer; }

private:
    Renderer& m_renderer;
};

}
