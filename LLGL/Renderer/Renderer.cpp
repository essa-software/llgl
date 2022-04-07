#include "Renderer.hpp"

#include "Renderable.hpp"
#include "LLGL/OpenGL/Vertex.hpp"

namespace llgl
{

void Renderer::render_object(Renderable const& renderable)
{
    renderable.render(*this);
}

void Renderer::add_triangle(Vertex _1, Vertex _2, Vertex _3)
{
    auto data = {_1, _2, _3};
    add_vertexes(data);
}

}
