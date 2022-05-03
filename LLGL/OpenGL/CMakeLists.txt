set(SOURCES
    Blend.cpp
    Error.cpp
    Extensions.cpp
    Shader.cpp
    Texture.cpp
    Transform.cpp
    Utils.cpp
    VAO.cpp
    Vertex.cpp
    View.cpp

    Shaders/Basic330Core.cpp
    Shaders/ShadeFlat.cpp
)
add_llgl_library(OpenGL opengl)
target_link_libraries(OpenGL GL GLU GLEW)
