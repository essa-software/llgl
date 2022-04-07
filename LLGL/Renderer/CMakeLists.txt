set(SOURCES
    BatchRenderer.cpp
    CoreRenderer.cpp
    FFPRenderer.cpp
    Renderer.cpp
    Transform.cpp
    View.cpp
)
add_llgl_library(Renderer renderer)
target_link_libraries(Renderer Window)
