#pragma once

#include <GL/glew.h>

#include <EssaUtil/Color.hpp>
#include <EssaUtil/EnumBits.hpp>
#include <GL/gl.h>
#include <LLGL/Core/Vector2.hpp>
#include <LLGL/Core/Vector3.hpp>

namespace llgl::opengl {

enum class PrimitiveType {
    Invalid = -1,
    Points = GL_POINTS,
    Lines = GL_LINES,
    Triangles = GL_TRIANGLES,
    TriangleStrip = GL_TRIANGLE_STRIP,
};

void begin(PrimitiveType);
void end();

class DrawScope {
public:
    DrawScope(PrimitiveType type) { begin(type); }
    ~DrawScope() { end(); }
};

void set_vertex_color(Util::Colorf);
void set_texture_coordinate(Vector2f);
void add_vertex(Vector3f);

}
