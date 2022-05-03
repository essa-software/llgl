#include "LLGL/Core/Color.hpp"
#include "LLGL/OpenGL/Shaders/ShadeFlat.hpp"
#include "LLGL/Renderer/Transform.hpp"
#include <LLGL/3D/ObjLoader.hpp>
#include <LLGL/3D/Object3D.hpp>
#include <LLGL/Core/Angle.hpp>
#include <LLGL/OpenGL/Shader.hpp>
#include <LLGL/OpenGL/Shaders/Basic330Core.hpp>
#include <LLGL/OpenGL/Utils.hpp>
#include <LLGL/Renderer/BatchRenderer.hpp>
#include <LLGL/Renderer/Renderer.hpp>
#include <LLGL/Window/Window.hpp>
#include <iostream>

int main()
{
    llgl::Window window { { 500, 500 }, u8"OBJ loader", { 3, 2 } };

    llgl::opengl::enable(llgl::opengl::Feature::DepthTest);
    llgl::opengl::set_clear_color(llgl::Color { 255, 128, 128 });

    auto object = llgl::ObjLoader::load_object_from_file("../car.obj");
    if (!object.has_value())
    {
        std::cerr << "FAILED TO READ :((" << std::endl;
        return 1;
    }

    llgl::Transform model_transform;
    model_transform = model_transform.translate({ -1.5, -1.5, -5 }).rotate_y(llgl::deg_to_rad(45));

    llgl::opengl::shaders::ShadeFlat shader;

    double light_angle = 0;

    double yaw = 0;
    double pitch = 0;

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
        model_transform = model_transform.rotate_x(0.05);
        llgl::Transform view_transform;
        view_transform = view_transform.rotate_y(yaw).rotate_x(pitch).translate({0, 0, -10});

        light_angle += 0.01;
        shader.set_light_position({ static_cast<float>(std::sin(light_angle)), 5, static_cast<float>(std::cos(light_angle)) });

        {
            shader.set_light_color(llgl::Colors::red * 0.8);
            window.renderer().render_object(object.value(), {
                                                                .shader = &shader,
                                                                .model_matrix = model_transform.matrix(),
                                                                .view_matrix = view_transform.matrix(),
                                                            });
        }

        {
            shader.set_light_color(llgl::Colors::green * 0.8);
            window.renderer().render_object(object.value(), {
                                                                .shader = &shader,
                                                                .model_matrix = model_transform.translate({ 3, 0, 0 }).matrix(),
                                                                .view_matrix = view_transform.matrix(),
                                                            });
        }

        window.display();
    }
    return 0;
}
