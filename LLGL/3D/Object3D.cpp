#include "Object3D.hpp"
#include "LLGL/OpenGL/Vertex.hpp"

#include <LLGL/OpenGL/Shader.hpp>
#include <LLGL/Renderer/Renderer.hpp>
#include <iostream>

#define OBJECT3D_DEBUG 0

namespace llgl
{

void Object3D::add_face(Face face)
{
    if constexpr (OBJECT3D_DEBUG)
    {
        m_normal_vertexes.push_back(Vertex { .position = face.v1.position });
        m_normal_vertexes.push_back(Vertex { .position = face.v1.position + face.v1.normal });
        m_normal_vertexes.push_back(Vertex { .position = face.v2.position });
        m_normal_vertexes.push_back(Vertex { .position = face.v2.position + face.v2.normal });
        m_normal_vertexes.push_back(Vertex { .position = face.v3.position });
        m_normal_vertexes.push_back(Vertex { .position = face.v3.position + face.v3.normal });
    }
    m_vertexes.push_back(std::move(face.v1));
    m_vertexes.push_back(std::move(face.v2));
    m_vertexes.push_back(std::move(face.v3));
    m_needs_update = true;
}

void Object3D::add_face(std::span<Vertex> face)
{
    if (face.size() < 3)
        return;
    for (size_t s = 0; s < face.size() - 2; s++)
    {
        m_vertexes.push_back(face[0]);
        m_vertexes.push_back(face[s + 1]);
        m_vertexes.push_back(face[s + 2]);

        if constexpr (OBJECT3D_DEBUG)
        {
            m_normal_vertexes.push_back(Vertex { .position = face[0].position });
            m_normal_vertexes.push_back(Vertex { .position = face[0].position + face[0].normal });
            m_normal_vertexes.push_back(Vertex { .position = face[s + 1].position });
            m_normal_vertexes.push_back(Vertex { .position = face[s + 1].position + face[s + 1].normal });
            m_normal_vertexes.push_back(Vertex { .position = face[s + 2].position });
            m_normal_vertexes.push_back(Vertex { .position = face[s + 2].position + face[s + 2].normal });
        }
    }
    for (auto& v : m_normal_vertexes)
        std::cout << v.position << std::endl;
    m_needs_update = true;
}

void Object3D::render(Renderer& renderer) const
{
    if (m_needs_update)
    {
        std::cerr << "needs update!" << std::endl;
        m_vao.load_vertexes(opengl::AttributeMapping { 1, 2, 3, 4 }, m_vertexes);
        if constexpr (OBJECT3D_DEBUG)
            m_normals_vao.load_vertexes(opengl::AttributeMapping { 1, 2, 3, 4 }, m_normal_vertexes);
        m_needs_update = false;
    }
    // TODO: Support custom config
    m_vao.draw(renderer, { .primitive_type = opengl::PrimitiveType::Triangles, .shader = m_shader, .modelview_matrix = m_transform.matrix() });

    if constexpr (OBJECT3D_DEBUG)
        m_normals_vao.draw(renderer, { .primitive_type = opengl::PrimitiveType::Lines, .shader = m_shader, .modelview_matrix = m_transform.matrix() });
}

}
