cmake_minimum_required(VERSION 3.8)
add_definitions(-DPROJECT_ROOT_DIR)
add_executable(01_triangle
    "01_triangle.cpp"
)

target_link_libraries(01_triangle PRIVATE engine)