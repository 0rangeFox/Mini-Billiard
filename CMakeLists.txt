cmake_minimum_required(VERSION 3.0)
project(Mini_Billiard)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.c src/*.cc src/*.cpp src/*.hpp src/*.h)

set(CMAKE_CXX_STANDARD 98)

add_executable(${PROJECT_NAME} ${sources})

add_subdirectory(libs/glfw)
add_subdirectory(libs/glew)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw libglew_static)
