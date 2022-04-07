#include "Object3D.hpp"
#include "LLGL/OpenGL/Vertex.hpp"

#include <LLGL/OpenGL/Shader.hpp>
#include <LLGL/Renderer/Renderer.hpp>
#include <iostream>

namespace llgl
{

void Object3D::add_face(Face face)
{
    m_vertexes.push_back(std::move(face.v1));
    m_vertexes.push_back(std::move(face.v2));
    m_vertexes.push_back(std::move(face.v3));
    m_needs_update = true;
}

void Object3D::add_face(std::span<Vertex> face)
{
    if(face.size() < 3)
        return;
    for(size_t s = 0; s < face.size() - 2; s++)
    {
        m_vertexes.push_back(face[0]);
        m_vertexes.push_back(face[s + 1]);
        m_vertexes.push_back(face[s + 2]);
    }
    m_needs_update = true;
}

void Object3D::render(Renderer& renderer) const
{
    if(m_needs_update)
    {
        std::cerr << "needs update!" << std::endl;
        m_vao.load_vertexes(opengl::AttributeMapping{1,2,3,4}, m_vertexes);
        m_needs_update = false;
    }
    // TODO: Support custom config
    m_vao.draw(renderer, {
        .primitive_type = opengl::PrimitiveType::Triangles,
        .shader = &opengl::shaders::basic_330_core(),
        .modelview_matrix = m_transform.matrix()
    });
}

}
