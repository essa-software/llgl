#include "FFPRenderer.hpp"
#include "LLGL/OpenGL/Transform.hpp"

#include <LLGL/OpenGL/Shader.hpp>

namespace llgl {

void FFPRenderer::begin_draw(opengl::PrimitiveType primitive_type, DrawState state)
{
    opengl::ShaderScope scope(*state.shader);
    opengl::begin(primitive_type);
}

void FFPRenderer::add_vertexes(std::span<Vertex const> vertexes)
{
    for (auto const& vertex : vertexes) {
        opengl::set_vertex_color(vertex.color);
        opengl::set_texture_coordinate(vertex.tex_coord);
        opengl::add_vertex(vertex.position);
    }
}

void FFPRenderer::end_draw()
{
    opengl::end();
}

void FFPRenderer::apply_view(View const& view)
{
    opengl::set_matrix_mode(opengl::MatrixMode::Projection);
    opengl::load_identity();
    opengl::set_viewport(view.viewport());
    switch (view.type()) {
        case View::Type::Ortho:
            opengl::load_ortho(view.ortho_args());
            break;
        case View::Type::Perspective:
            opengl::load_perspective(view.perspective_args());
            break;
    }
}

}
