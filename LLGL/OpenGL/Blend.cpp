#include "Blend.hpp"

#include "Error.hpp"

namespace llgl::opengl
{

void set_blend_func(BlendFunc source, BlendFunc destination)
{
    ErrorHandler handler;
    glBlendFunc((GLenum)source, (GLenum)destination);
}

}
