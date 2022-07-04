#include "Shapes.hpp"

namespace llgl::Shapes {

void add_cube(std::vector<Vertex>& vertices, Transform const& transform)
{
    // left
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, -1, -1 }), .color = llgl::Colors::white, .normal = { -1, 0, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, 1, -1 }), .color = llgl::Colors::white, .normal = { -1, 0, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, -1, 1 }), .color = llgl::Colors::white, .normal = { -1, 0, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, 1, -1 }), .color = llgl::Colors::white, .normal = { -1, 0, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, -1, 1 }), .color = llgl::Colors::white, .normal = { -1, 0, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, 1, 1 }), .color = llgl::Colors::white, .normal = { -1, 0, 0 } });

    // right
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, -1, -1 }), .color = llgl::Colors::white, .normal = { 1, 0, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, 1, -1 }), .color = llgl::Colors::white, .normal = { 1, 0, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, -1, 1 }), .color = llgl::Colors::white, .normal = { 1, 0, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, 1, -1 }), .color = llgl::Colors::white, .normal = { 1, 0, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, -1, 1 }), .color = llgl::Colors::white, .normal = { 1, 0, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, 1, 1 }), .color = llgl::Colors::white, .normal = { 1, 0, 0 } });

    // bottom
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, -1, -1 }), .color = llgl::Colors::white, .normal = { 0, -1, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, -1, -1 }), .color = llgl::Colors::white, .normal = { 0, -1, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, -1, 1 }), .color = llgl::Colors::white, .normal = { 0, -1, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, -1, -1 }), .color = llgl::Colors::white, .normal = { 0, -1, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, -1, 1 }), .color = llgl::Colors::white, .normal = { 0, -1, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, -1, 1 }), .color = llgl::Colors::white, .normal = { 0, -1, 0 } });

    // top
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, 1, -1 }), .color = llgl::Colors::white, .normal = { 0, 1, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, 1, -1 }), .color = llgl::Colors::white, .normal = { 0, 1, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, 1, 1 }), .color = llgl::Colors::white, .normal = { 0, 1, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, 1, -1 }), .color = llgl::Colors::white, .normal = { 0, 1, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, 1, 1 }), .color = llgl::Colors::white, .normal = { 0, 1, 0 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, 1, 1 }), .color = llgl::Colors::white, .normal = { 0, 1, 0 } });

    // front
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, -1, -1 }), .color = llgl::Colors::white, .normal = { 0, 0, -1 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, -1, -1 }), .color = llgl::Colors::white, .normal = { 0, 0, -1 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, 1, -1 }), .color = llgl::Colors::white, .normal = { 0, 0, -1 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, -1, -1 }), .color = llgl::Colors::white, .normal = { 0, 0, -1 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, 1, -1 }), .color = llgl::Colors::white, .normal = { 0, 0, -1 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, 1, -1 }), .color = llgl::Colors::white, .normal = { 0, 0, -1 } });

    // back
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, -1, 1 }), .color = llgl::Colors::white, .normal = { 0, 0, 1 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, -1, 1 }), .color = llgl::Colors::white, .normal = { 0, 0, 1 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, 1, 1 }), .color = llgl::Colors::white, .normal = { 0, 0, 1 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, -1, 1 }), .color = llgl::Colors::white, .normal = { 0, 0, 1 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ -1, 1, 1 }), .color = llgl::Colors::white, .normal = { 0, 0, 1 } });
    vertices.push_back(Vertex { .position = transform.transform_point({ 1, 1, 1 }), .color = llgl::Colors::white, .normal = { 0, 0, 1 } });
}

}
