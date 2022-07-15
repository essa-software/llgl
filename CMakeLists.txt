cmake_minimum_required(VERSION 3.19)
project(LLGL)
set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 COMPONENTS SDL2 SDL2_video SDL2_image SDL2_ttf REQUIRED)
find_package(GLEW REQUIRED)
find_package(EssaUtil REQUIRED)

add_subdirectory(LLGL)

install(FILES cmake/LLGLConfig.cmake DESTINATION lib/cmake/llgl)
install(DIRECTORY LLGL/ DESTINATION include/LLGL FILES_MATCHING PATTERN "*.hpp" PATTERN "*.inl")
install(EXPORT llgl DESTINATION lib/cmake/llgl NAMESPACE LLGL::)

add_subdirectory(Tests)
