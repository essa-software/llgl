function(add_llgl_library TARGET_NAME LIB_NAME)
    add_library(${TARGET_NAME} ${SOURCES})
    add_library(LLGL::${TARGET_NAME} ALIAS ${TARGET_NAME})
    set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME "llgl-${LIB_NAME}")
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Werror)
    target_compile_options(${TARGET_NAME} PRIVATE
        -Wnon-virtual-dtor
        -Wno-error=missing-field-initializers
        -Wno-error=format
    )
    target_include_directories(${TARGET_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)
    install(TARGETS ${TARGET_NAME} EXPORT llgl DESTINATION lib)
endfunction()

add_subdirectory(3D)
add_subdirectory(EventLoop)
add_subdirectory(OpenGL)
add_subdirectory(Renderer)
add_subdirectory(Window)
