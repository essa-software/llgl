#include "Error.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

namespace llgl::opengl
{

void handle_error(std::source_location location)
{
    auto error = glGetError();
    if(error != GL_NO_ERROR)
    {
        std::cout << "GLError! " << gluErrorString(error)
            << " at " << location.function_name() << " " << location.file_name() << ":" << location.line() << ":" << location.column() << std::endl;
        //abort();
    }
}

}
