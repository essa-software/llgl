#include "Cube.hpp"
#include "LLGL/3D/Shapes.hpp"

#include <LLGL/Renderer/Renderer.hpp>

namespace llgl {

Cube::Cube(opengl::AttributeMapping mapping)
{
    generate(mapping);
}

void Cube::generate(opengl::AttributeMapping mapping)
{
    std::vector<Vertex> vertices;
    Shapes::add_cube(vertices);
    m_vao.load_vertexes(mapping, vertices);
}

void Cube::render(Renderer& renderer, DrawState state) const
{
    renderer.draw_vao(m_vao, opengl::PrimitiveType::Triangles, state);
}

}
