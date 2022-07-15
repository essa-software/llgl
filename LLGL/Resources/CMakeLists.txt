set(SOURCES
    ImageLoader.cpp
)
add_llgl_library(Resources resources)
target_link_libraries(Resources Core SDL2_image)
