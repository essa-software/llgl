#include <LLGL/Core/Color.hpp>
#include <LLGL/OpenGL/Blend.hpp>
#include <LLGL/OpenGL/Shaders/Basic330Core.hpp>
#include <LLGL/OpenGL/Transform.hpp>
#include <LLGL/OpenGL/Utils.hpp>
#include <LLGL/OpenGL/Vertex.hpp>
#include <LLGL/OpenGL/View.hpp>
#include <LLGL/Renderer/BatchRenderer.hpp>
#include <LLGL/Renderer/Renderer.hpp>
#include <LLGL/Window/Window.hpp>

int main()
{
    llgl::Window window { { 500, 500 }, u8"core renderer", { 3, 2 } };

    std::vector<llgl::Colorf> color_array;
    color_array.resize(256 * 256);
    for (size_t y = 0; y < 256; y++)
    {
        for (size_t x = 0; x < 256; x++)
        {
            color_array[y * 256 + x] = llgl::Colorf {
                static_cast<float>((double)rand() / RAND_MAX),
                static_cast<float>((double)rand() / RAND_MAX),
                static_cast<float>((double)rand() / RAND_MAX),
                0.5f
            };
        }
    }
    llgl::opengl::Texture texture = llgl::opengl::Texture::create_from_color_array({ 256, 256 }, color_array.data());

    llgl::opengl::enable(llgl::opengl::Feature::Blend);
    llgl::opengl::enable(llgl::opengl::Feature::DepthTest);
    llgl::opengl::set_blend_func(llgl::opengl::BlendFunc::SrcAlpha, llgl::opengl::BlendFunc::OneMinusSrcAlpha);
    llgl::opengl::set_clear_color(llgl::Color { 255, 128, 128 });
    llgl::BatchRenderer batch_renderer { window };

    llgl::opengl::shaders::Basic330Core shader;
    {
        llgl::DrawScope scope { batch_renderer, llgl::opengl::PrimitiveType::Triangles, { .shader = &shader, .texture = &texture } };
        batch_renderer.add_triangle(
            { { -1.5, -1.5, -15 }, llgl::Colors::white, { 0, 0 } },
            { { 1.5, 1.5, -15 }, llgl::Colors::white, { 1, 1 } },
            { { 1.5, -1.5, -15 }, llgl::Colors::white, { 1, 0 } });
        batch_renderer.add_triangle(
            { { -1.5, -1.5, -10 }, llgl::Colors::white, { 0, 0 } },
            { { 1.5, 1.5, -10 }, llgl::Colors::white, { 1, 1 } },
            { { 1.5, -1.5, -10 }, llgl::Colors::white, { 1, 0 } });
    }

    for (;;)
    {
        llgl::Event event;
        while (window.poll_event(event))
        {
        }
        llgl::opengl::clear(llgl::opengl::ClearMask::Color | llgl::opengl::ClearMask::Depth);

        llgl::View view;
        view.set_viewport(llgl::Recti { 0, 0, window.size().x, window.size().y });
        view.set_perspective({ 1.22, window.aspect(), 0.1, 20 });
        window.renderer().apply_view(view);
        window.renderer().render_object(batch_renderer, {});
        window.display();
    }
    return 0;
}
