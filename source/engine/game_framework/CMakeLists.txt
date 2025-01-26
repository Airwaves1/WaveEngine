cmake_minimum_required(VERSION 3.8)

# 递归搜索所有的.cpp文件
file(GLOB_RECURSE game_framework_source CONFIGURE_DEPENDS *.cpp)

add_library(game_framework STATIC ${game_framework_source})

target_link_libraries(game_framework PUBLIC core)