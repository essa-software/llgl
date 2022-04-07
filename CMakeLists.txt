cmake_minimum_required(VERSION 3.19)
project(LLGL)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
message("found SDL2")

add_subdirectory(LLGL)

install(FILES cmake/LLGLConfig.cmake DESTINATION lib/cmake/llgl)
install(DIRECTORY LLGL DESTINATION include FILES_MATCHING PATTERN "*.h" PATTERN "*.inl")
install(EXPORT llgl DESTINATION lib/cmake/llgl)

add_subdirectory(Tests)
