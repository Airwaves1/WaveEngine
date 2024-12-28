cmake_minimum_required(VERSION 3.8)

add_library(external INTERFACE)

# glfw
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(glfw)

# glad
add_subdirectory(glad)

# glm
add_subdirectory(glm)
option(GLM_ENABLE_EXPERIMENTAL ON)
option(GLM_ENABLE_CXX_20 "Enable C++ 20 features" ON)

target_link_libraries(external INTERFACE glfw)
target_link_libraries(external INTERFACE glad)
target_link_libraries(external INTERFACE glm)