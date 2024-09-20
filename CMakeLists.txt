cmake_minimum_required(VERSION 3.30.1)
project(Learn-OpenGL-F VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL        OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

add_library(glad lib/Glad/glad.c)
target_include_directories(glad PUBLIC include/Glad)
set_target_properties(glad PROPERTIES FOLDER "Glad")

set(${CMAKE_PROJECT_NAME}_CONFIG_ROOT_PATH_SHADER_FILES_DIRECTORY ${PROJECT_SOURCE_DIR}/src/shaders/)
configure_file(src/config.h.in src/config.h)
configure_file(src/version.h.in src/version.h)
add_executable(
    learn-opengl-f
    src/main.cpp
    src/shader.cpp
    src/shader.hpp
    src/shaders/shader_fragment.glsl
    src/shaders/shader_vertex.glsl
    src/config.h
    src/version.h
)
source_group(
    "Shader Files" FILES
    src/shaders/shader_fragment.glsl
    src/shaders/shader_vertex.glsl
)
target_include_directories(
    learn-opengl-f
    PUBLIC
    ${PROJECT_BINARY_DIR}/src
)
target_link_libraries(learn-opengl-f PRIVATE glfw glad)
set_target_properties(learn-opengl-f PROPERTIES OUTPUT_NAME "Learn-OpenGL-F")

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT learn-opengl-f)