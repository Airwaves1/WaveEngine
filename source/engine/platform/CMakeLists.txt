cmake_minimum_required(VERSION 3.8)

file(GLOB_RECURSE platform_sources CONFIGURE_DEPENDS "*.cpp")

add_library(platform STATIC ${platform_sources})

target_link_libraries(platform PUBLIC external)