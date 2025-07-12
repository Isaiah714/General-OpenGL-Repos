cmake_minimum_required(VERSION 4.0.0)

project(General-OpenGL)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(opengl src/main.cpp lib/src/glad.c)

target_link_libraries(opengl PRIVATE OpenGL::GL glfw)