cmake_minimum_required(VERSION 3.8)

add_library(external INTERFACE)

# glfw
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(glfw)

# glad
add_subdirectory(glad)