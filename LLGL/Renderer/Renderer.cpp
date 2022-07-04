#include "Renderer.hpp"

#include "LLGL/OpenGL/Utils.hpp"
#include "Renderable.hpp"

#include <LLGL/OpenGL/Vertex.hpp>
#include <LLGL/Renderer/StateScope.hpp>

namespace llgl {

void Renderer::clear(std::optional<llgl::Color> color)
{
    if (color)
        opengl::set_clear_color(*color);
    opengl::clear_enabled();
}

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
    vao.draw(state.shader->attribute_mapping(), primitive_type);
}

void Renderer::draw_vao_with_indices(opengl::VAO const& vao, opengl::PrimitiveType primitive_type, DrawState const& state, std::span<unsigned const> indices)
{
    StateScope scope(state, view());
    vao.draw_indexed(state.shader->attribute_mapping(), primitive_type, indices);
}

}
