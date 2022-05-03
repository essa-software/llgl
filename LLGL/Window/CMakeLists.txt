set(SOURCES
    Impls/SDLWindow.cpp
    Keyboard.cpp
    Window.cpp
)
add_llgl_library(Window window)
target_link_libraries(Window SDL2 Renderer)
