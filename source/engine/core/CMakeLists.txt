cmake_minimum_required(VERSION 3.8)

# 递归搜索所有的.cpp文件
file(GLOB_RECURSE core_source CONFIGURE_DEPENDS *.cpp)

add_library(core STATIC ${core_source})

target_link_libraries(core PUBLIC platform)