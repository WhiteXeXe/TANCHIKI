cmake_minimum_required(VERSION 3.28)
project(Tanchiki C)

set(CMAKE_C_STANDARD 23)

add_executable(Tanchiki main.c)
target_link_libraries(Tanchiki PRIVATE $<IF:$<TARGET_EXISTS:FreeGLUT::freeglut>,FreeGLUT::freeglut,FreeGLUT::freeglut_static>)
find_package(FreeGLUT CONFIG REQUIRED)