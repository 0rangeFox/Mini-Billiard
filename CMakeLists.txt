cmake_minimum_required(VERSION 3.5)
project(Mini_Billiard)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules/")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.c src/*.cc src/*.cpp src/*.hpp src/*.h)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} ${sources})

include(STB)

add_subdirectory(libs/glfw)
add_subdirectory(libs/glew)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw libglew_static stb)
