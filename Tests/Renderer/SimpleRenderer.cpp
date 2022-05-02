#include <LLGL/Core/Color.hpp>
#include <LLGL/OpenGL/Transform.hpp>
#include <LLGL/OpenGL/Utils.hpp>
#include <LLGL/OpenGL/Vertex.hpp>
#include <LLGL/OpenGL/View.hpp>
#include <LLGL/Renderer/Renderer.hpp>
#include <LLGL/Window/Window.hpp>

int main()
{
    llgl::Window window { { 500, 500 }, u8"simple renderer", { 2, 1 } };
    llgl::opengl::set_clear_color(llgl::Color { 255, 128, 128 });
    for (;;)
    {
        llgl::Event event;
        while (window.poll_event(event))
        {
        }
        llgl::opengl::clear(llgl::opengl::ClearMask::Color);

        llgl::View view;
        view.set_viewport(llgl::Recti { 0, 0, window.size().x, window.size().y });
        view.set_ortho(llgl::Rectd { 0, 0, static_cast<double>(window.size().x), static_cast<double>(window.size().y) });
        window.renderer().apply_view(view);

        {
            llgl::opengl::set_scissor({ 0, 0, 200, 200 });
            llgl::DrawScope scope { window.renderer(), { llgl::opengl::PrimitiveType::Triangles } };
            scope.renderer().add_triangle(
                { { 150, 100, 0 }, llgl::Colors::green },
                { { 200, 200, 0 }, llgl::Colors::red },
                { { 100, 200, 0 }, llgl::Colors::blue });
        }

        window.display();
    }
    return 0;
}
