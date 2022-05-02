#pragma once

#include <LLGL/Core/Vertex.hpp>
#include <LLGL/OpenGL/VAO.hpp>
#include <LLGL/Renderer/Renderable.hpp>
#include <LLGL/Renderer/Transform.hpp>
#include <vector>

namespace llgl
{

class Object3D : public Renderable
{
public:
    struct Face
    {
        Vertex v1, v2, v3;
    };

    void add_face(Face face);
    void add_face(std::span<Vertex>);

    Transform& transform() { return m_transform; }
    Transform const& transform() const { return m_transform; }

    RendererConfig& renderer_config() { return m_renderer_config; }
    RendererConfig const& renderer_config() const { return m_renderer_config; }
 
private:
    virtual void render(Renderer& renderer) const override;

    std::vector<Vertex> m_vertexes;
    std::vector<Vertex> m_normal_vertexes;
    Transform m_transform;
    RendererConfig m_renderer_config;
    mutable opengl::VAO m_vao;
    mutable opengl::VAO m_normals_vao;
    mutable bool m_needs_update { true };
};

}
