cmake_minimum_required(VERSION 3.19)
project(LLGL)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
message("found SDL2")

add_subdirectory(LLGL)

install(FILES cmake/LLGLConfig.cmake DESTINATION lib/cmake/llgl)
install(DIRECTORY LLGL/ DESTINATION include/LLGL FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl")
install(EXPORT llgl DESTINATION lib/cmake/llgl NAMESPACE LLGL::)

add_subdirectory(Tests)
