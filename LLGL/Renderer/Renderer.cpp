#include "Renderer.hpp"

#include "Renderable.hpp"

#include <LLGL/OpenGL/Vertex.hpp>
#include <LLGL/Renderer/StateScope.hpp>

namespace llgl
{

void Renderer::render_object(Renderable const& renderable, DrawState state)
{
    renderable.render(*this, state);
}

void Renderer::add_triangle(Vertex _1, Vertex _2, Vertex _3)
{
    auto data = { _1, _2, _3 };
    add_vertexes(data);
}

void Renderer::draw_vao(opengl::VAO const& vao, opengl::PrimitiveType primitive_type, DrawState const& state)
{
    StateScope scope(state, view());
    vao.draw(primitive_type);
}

}
