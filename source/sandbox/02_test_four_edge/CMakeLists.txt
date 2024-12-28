cmake_minimum_required(VERSION 3.8)
add_executable(02_test_four_edge
    "02_test_four_edge.cpp"
)

target_link_libraries(02_test_four_edge PRIVATE engine)