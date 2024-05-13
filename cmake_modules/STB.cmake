add_library(stb INTERFACE)
target_include_directories(stb INTERFACE SYSTEM "${CMAKE_CURRENT_SOURCE_DIR}/libs/stb" "stb")
