#include "Cube.hpp"

#include <LLGL/Renderer/Renderer.hpp>

namespace llgl {

Cube::Cube(opengl::AttributeMapping mapping)
{
    generate(mapping);
}

void Cube::generate(opengl::AttributeMapping mapping)
{
    std::vector<Vertex> vertices;

    // left
    vertices.push_back(Vertex { .position = { -1, -1, -1 }, .color = llgl::Colors::white, .normal = { -1, 0, 0 } });
    vertices.push_back(Vertex { .position = { -1, 1, -1 }, .color = llgl::Colors::white, .normal = { -1, 0, 0 } });
    vertices.push_back(Vertex { .position = { -1, -1, 1 }, .color = llgl::Colors::white, .normal = { -1, 0, 0 } });
    vertices.push_back(Vertex { .position = { -1, 1, -1 }, .color = llgl::Colors::white, .normal = { -1, 0, 0 } });
    vertices.push_back(Vertex { .position = { -1, -1, 1 }, .color = llgl::Colors::white, .normal = { -1, 0, 0 } });
    vertices.push_back(Vertex { .position = { -1, 1, 1 }, .color = llgl::Colors::white, .normal = { -1, 0, 0 } });

    // right
    vertices.push_back(Vertex { .position = { 1, -1, -1 }, .color = llgl::Colors::white, .normal = { 1, 0, 0 } });
    vertices.push_back(Vertex { .position = { 1, 1, -1 }, .color = llgl::Colors::white, .normal = { 1, 0, 0 } });
    vertices.push_back(Vertex { .position = { 1, -1, 1 }, .color = llgl::Colors::white, .normal = { 1, 0, 0 } });
    vertices.push_back(Vertex { .position = { 1, 1, -1 }, .color = llgl::Colors::white, .normal = { 1, 0, 0 } });
    vertices.push_back(Vertex { .position = { 1, -1, 1 }, .color = llgl::Colors::white, .normal = { 1, 0, 0 } });
    vertices.push_back(Vertex { .position = { 1, 1, 1 }, .color = llgl::Colors::white, .normal = { 1, 0, 0 } });

    // bottom
    vertices.push_back(Vertex { .position = { -1, -1, -1 }, .color = llgl::Colors::white, .normal = { 0, -1, 0 } });
    vertices.push_back(Vertex { .position = { 1, -1, -1 }, .color = llgl::Colors::white, .normal = { 0, -1, 0 } });
    vertices.push_back(Vertex { .position = { -1, -1, 1 }, .color = llgl::Colors::white, .normal = { 0, -1, 0 } });
    vertices.push_back(Vertex { .position = { 1, -1, -1 }, .color = llgl::Colors::white, .normal = { 0, -1, 0 } });
    vertices.push_back(Vertex { .position = { -1, -1, 1 }, .color = llgl::Colors::white, .normal = { 0, -1, 0 } });
    vertices.push_back(Vertex { .position = { 1, -1, 1 }, .color = llgl::Colors::white, .normal = { 0, -1, 0 } });

    // top
    vertices.push_back(Vertex { .position = { -1, 1, -1 }, .color = llgl::Colors::white, .normal = { 0, 1, 0 } });
    vertices.push_back(Vertex { .position = { 1, 1, -1 }, .color = llgl::Colors::white, .normal = { 0, 1, 0 } });
    vertices.push_back(Vertex { .position = { -1, 1, 1 }, .color = llgl::Colors::white, .normal = { 0, 1, 0 } });
    vertices.push_back(Vertex { .position = { 1, 1, -1 }, .color = llgl::Colors::white, .normal = { 0, 1, 0 } });
    vertices.push_back(Vertex { .position = { -1, 1, 1 }, .color = llgl::Colors::white, .normal = { 0, 1, 0 } });
    vertices.push_back(Vertex { .position = { 1, 1, 1 }, .color = llgl::Colors::white, .normal = { 0, 1, 0 } });

    // front
    vertices.push_back(Vertex { .position = { -1, -1, -1 }, .color = llgl::Colors::white, .normal = { 0, 0, -1 } });
    vertices.push_back(Vertex { .position = { 1, -1, -1 }, .color = llgl::Colors::white, .normal = { 0, 0, -1 } });
    vertices.push_back(Vertex { .position = { -1, 1, -1 }, .color = llgl::Colors::white, .normal = { 0, 0, -1 } });
    vertices.push_back(Vertex { .position = { 1, -1, -1 }, .color = llgl::Colors::white, .normal = { 0, 0, -1 } });
    vertices.push_back(Vertex { .position = { -1, 1, -1 }, .color = llgl::Colors::white, .normal = { 0, 0, -1 } });
    vertices.push_back(Vertex { .position = { 1, 1, -1 }, .color = llgl::Colors::white, .normal = { 0, 0, -1 } });

    // back
    vertices.push_back(Vertex { .position = { -1, -1, 1 }, .color = llgl::Colors::white, .normal = { 0, 0, 1 } });
    vertices.push_back(Vertex { .position = { 1, -1, 1 }, .color = llgl::Colors::white, .normal = { 0, 0, 1 } });
    vertices.push_back(Vertex { .position = { -1, 1, 1 }, .color = llgl::Colors::white, .normal = { 0, 0, 1 } });
    vertices.push_back(Vertex { .position = { 1, -1, 1 }, .color = llgl::Colors::white, .normal = { 0, 0, 1 } });
    vertices.push_back(Vertex { .position = { -1, 1, 1 }, .color = llgl::Colors::white, .normal = { 0, 0, 1 } });
    vertices.push_back(Vertex { .position = { 1, 1, 1 }, .color = llgl::Colors::white, .normal = { 0, 0, 1 } });

    m_vao.load_vertexes(mapping, vertices);
}

void Cube::render(Renderer& renderer, DrawState state) const
{
    renderer.draw_vao(m_vao, opengl::PrimitiveType::Triangles, state);
}

}
