#include <LLGL/3D/Sphere.hpp>
#include <LLGL/Core/Angle.hpp>
#include <LLGL/OpenGL/Shaders/ShadeFlat.hpp>
#include <LLGL/OpenGL/Utils.hpp>
#include <LLGL/Renderer/Transform.hpp>
#include <LLGL/Window/Window.hpp>

int main()
{

    llgl::Window window { { 500, 500 }, u8"Spheres", { 3, 2 } };

    llgl::opengl::enable(llgl::opengl::Feature::DepthTest);
    llgl::opengl::set_clear_color(llgl::Color { 255, 128, 128 });

    llgl::opengl::shaders::ShadeFlat shader;
    llgl::Sphere sphere { shader.attribute_mapping() };

    llgl::Transform model_transform;
    model_transform = model_transform.translate({ -1.5, -1.5, -5 }).rotate_y(llgl::deg_to_rad(45));

    double light_angle = 0;
    double yaw = 0;
    double pitch = 0;

    for (;;) {
        llgl::Event event;
        while (window.poll_event(event)) {
        }
        llgl::opengl::clear(llgl::opengl::ClearMask::Color | llgl::opengl::ClearMask::Depth);

        llgl::View view;
        view.set_viewport(llgl::Recti { 0, 0, window.size().x, window.size().y });
        view.set_perspective({ 1.22, window.aspect(), 0.1, 20 });
        window.renderer().apply_view(view);
        model_transform = model_transform.rotate_x(0.05);

        llgl::Transform view_transform;
        view_transform = view_transform.rotate_y(yaw).rotate_x(pitch);

        light_angle += 0.01;
        shader.set_light_position({ static_cast<float>(std::sin(light_angle)), 5, static_cast<float>(std::cos(light_angle)) });

        {
            shader.set_light_color(llgl::Colors::red * 0.8);
            window.renderer().render_object(sphere, {
                                                        .shader = &shader,
                                                        .model_matrix = model_transform.matrix(),
                                                        .view_matrix = view_transform.matrix(),
                                                    });
        }

        {
            shader.set_light_color(llgl::Colors::green * 0.8);
            window.renderer().render_object(sphere, {
                                                        .shader = &shader,
                                                        .model_matrix = model_transform.translate({ 3, 0, 0 }).matrix(),
                                                        .view_matrix = view_transform.matrix(),
                                                    });
        }

        window.display();
    }
    return 0;
}
