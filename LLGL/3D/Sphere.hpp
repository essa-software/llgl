#pragma once

#include <GL/glew.h>

#include <LLGL/Core/Color.hpp>
#include <LLGL/Core/Vector3.hpp>
#include <LLGL/OpenGL/VAO.hpp>
#include <LLGL/Renderer/Renderable.hpp>
#include <vector>

namespace llgl {

class Sphere : public Renderable {
public:
    explicit Sphere();
    virtual void render(Renderer&, DrawState) const override;

private:
    void generate();
    size_t vertex_index(unsigned stack, unsigned sector) const;

    opengl::VAO m_vao;
    std::vector<unsigned> m_indices;
};

}
