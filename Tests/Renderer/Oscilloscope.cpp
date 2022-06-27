#include <LLGL/Core/Color.hpp>
#include <LLGL/Core/DelayedInit.hpp>
#include <LLGL/OpenGL/FBO.hpp>
#include <LLGL/OpenGL/Vertex.hpp>
#include <LLGL/Renderer/Transform.hpp>
#include <LLGL/Window/Window.hpp>

#include <LLGL/OpenGL/Shader.hpp>
#include <LLGL/OpenGL/Utils.hpp>

static llgl::opengl::Program& shader()
{
    static llgl::DelayedInit<llgl::opengl::Program> program;
    if (!program.is_initialized()) {
        static char const* VERTEX_SHADER = R"~~~(
#version 410 core

layout(location=1) in vec4 position;
layout(location=2) in vec4 color;
layout(location=3) in vec2 texCoord;
layout(location=4) in vec3 normal;
out vec4 f_color;
uniform mat4 projectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;

void main()
{
    mat4 matrix = projectionMatrix * viewMatrix * modelMatrix;
    f_color = color;
    gl_Position = matrix * position;
}
)~~~";
        static char const* FRAGMENT_SHADER = R"~~~(
#version 410 core

uniform sampler2D accum;

in vec4 f_color;

void main()
{
    vec4 color = f_color;
    gl_FragColor = color;
}
)~~~";
        auto objects = {
            llgl::opengl::ShaderObject { VERTEX_SHADER, llgl::opengl::ShaderObject::Vertex },
            llgl::opengl::ShaderObject { FRAGMENT_SHADER, llgl::opengl::ShaderObject::Fragment }
        };
        program.construct(objects);
    }
    return *program.ptr();
}

class Shader : public llgl::opengl::Shader {
public:
    Shader()
        : llgl::opengl::Shader(shader())
    {
    }

    virtual llgl::opengl::AttributeMapping attribute_mapping() const override
    {
        return {
            .position = 1,
            .color = 2,
            .tex_coord = 3,
            .normal = 4
        };
    }

private:
    virtual void on_bind(llgl::opengl::ShaderScope&) const override
    {
    }
};

int main()
{
    llgl::Window window({ 512, 512 }, u8"Shot2");
    auto& renderer = window.renderer();
    Shader shader;

    llgl::opengl::VAO vao;
    vao.load_vertexes(shader.attribute_mapping(),
        { { llgl::Vertex { .position = { -5, -5, 0 }, .color = llgl::Colors::green },
            llgl::Vertex { .position = { 5, -5, 0 }, .color = llgl::Colors::green },
            llgl::Vertex { .position = { -5, 5, 0 }, .color = llgl::Colors::green },
            llgl::Vertex { .position = { 5, 5, 0 }, .color = llgl::Colors::green } } });

    llgl::opengl::FBO accum;

    for (;;) {
        llgl::Event event;
        while (window.poll_event(event)) {
            switch (event.type) {
                default:
                    break;
            }
        }

        llgl::opengl::clear(llgl::opengl::ClearMask::Color);

        llgl::View view;
        view.set_viewport(llgl::Recti { 0, 0, window.size().x, window.size().y });
        view.set_ortho({ { 0, 0, 512, 512 } });
        renderer.apply_view(view);

        auto mouse_position = llgl::mouse_position();

        llgl::Transform model = llgl::Transform {}.translate(llgl::Vector3f { mouse_position });

        renderer.draw_vao(vao, llgl::opengl::PrimitiveType::TriangleStrip, { .shader = &shader, .model_matrix = model.matrix() });

        window.display();
    }
    return 0;
}
