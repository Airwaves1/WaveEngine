cmake_minimum_required(VERSION 3.8)

add_executable(02_texture
    "02_texture.cpp"
)

target_link_libraries(02_texture PRIVATE engine)