cmake_minimum_required(VERSION 3.8)

add_library(engine INTERFACE)

target_link_libraries(engine INTERFACE game_framework)

add_subdirectory(core)
add_subdirectory(platform)
add_subdirectory(game_framework)