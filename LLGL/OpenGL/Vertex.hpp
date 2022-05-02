#pragma once

#include <LLGL/Core/Color.hpp>
#include <LLGL/Core/EnumBits.hpp>
#include <LLGL/Core/Vector2.hpp>
#include <LLGL/Core/Vector3.hpp>
#include <GL/glew.h>
#include <GL/gl.h>

namespace llgl::opengl
{

enum class PrimitiveType
{
    Invalid = -1,
    Points = GL_POINTS,
    Triangles = GL_TRIANGLES,
    TriangleStrip = GL_TRIANGLE_STRIP,
    Lines = GL_LINES,
};

void begin(PrimitiveType);
void end();

class DrawScope
{
public:
    DrawScope(PrimitiveType type) { begin(type); }
    ~DrawScope() { end(); }
};

void set_vertex_color(Colorf);
void set_texture_coordinate(Vector2f);
void add_vertex(Vector3f);

}
