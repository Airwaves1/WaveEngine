cmake_minimum_required(VERSION 3.8)

add_executable(04_ecs
    "04_ecs.cpp"
)

target_link_libraries(04_ecs PRIVATE engine)