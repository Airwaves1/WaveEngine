cmake_minimum_required(VERSION 3.8)

add_executable(03_camera
    "03_camera.cpp"
)

target_link_libraries(03_camera PRIVATE engine)