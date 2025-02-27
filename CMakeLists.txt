set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
cmake_minimum_required(VERSION 3.8)

project(WaveEngine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Os -Wall")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置可执行文件的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 设置库文件的输出目录（静态库和动态库）
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 设置不同构建类型的输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/lib/debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/lib/release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)

# 检查当前平台
if(WIN32)
    message(STATUS "Current Platform: Windows")
    add_definitions(-DPLATFORM_WINDOWS)
elseif(APPLE)
    message(STATUS "Current Platform: MacOS")
    add_definitions(-DPLATFORM_MACOS)
elseif(UNIX)
    message(STATUS "Current Platform: Linux")
    add_definitions(-DPLATFORM_LINUX)
else()
    message(FATAL_ERROR "Unsupported Platform")
endif()

# 添加其他宏定义
add_definitions(-DPROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")
set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

# 添加头文件搜索路径
include_directories(${CMAKE_SOURCE_DIR}/source/engine)
include_directories(${CMAKE_SOURCE_DIR}/source/engine/core)
include_directories(${CMAKE_SOURCE_DIR}/source/engine/platform)
include_directories(${CMAKE_SOURCE_DIR}/source/engine/game_framework)
    

# 添加第三方库头文件
include_directories(${CMAKE_SOURCE_DIR}/source/engine/external/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/source/engine/external/spdlog)
include_directories(${CMAKE_SOURCE_DIR}/source/engine/external/glm)
include_directories(${CMAKE_SOURCE_DIR}/source/engine/external/glad/include)
include_directories(${CMAKE_SOURCE_DIR}/source/engine/external/stb_image)
include_directories(${CMAKE_SOURCE_DIR}/source/engine/external/imgui)
include_directories(${CMAKE_SOURCE_DIR}/source/engine/external/nlohmann_json)
include_directories(${CMAKE_SOURCE_DIR}/source/engine/external)

# 添加子目录
add_subdirectory(source/engine)
add_subdirectory(source/engine/external)
add_subdirectory(source/sandbox)
