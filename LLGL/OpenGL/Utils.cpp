#include "Utils.hpp"

#include "Error.hpp"
#include <GL/gl.h>
#include <set>

namespace llgl::opengl
{

void set_clear_color(Color color)
{
    ErrorHandler handler;
    glClearColor(color.r / 255.f, color.g / 255.f, color.b / 255.f, color.a / 255.f);
}

void clear(ClearMask mask)
{
    ErrorHandler handler;
    glClear(static_cast<GLbitfield>(mask));
}

void enable(Feature feature)
{
    ErrorHandler handler;
    glEnable(static_cast<GLenum>(feature));
}

void disable(Feature feature)
{
    ErrorHandler handler;
    glDisable(static_cast<GLenum>(feature));
}

void ensure_enabled(Feature feature)
{
    if(is_enabled(feature))
        return;
    enable(feature);
}

bool is_enabled(Feature feature)
{
    ErrorHandler handler;
    return glIsEnabled(static_cast<GLenum>(feature));
}

void set_scissor(Recti rect)
{
    ensure_enabled(Feature::ScissorTest);
    ErrorHandler handler;
    glScissor(rect.left, rect.top, rect.width, rect.height);
}

}
