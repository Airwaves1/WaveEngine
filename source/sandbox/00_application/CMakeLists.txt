cmake_minimum_required(VERSION 3.8)

add_executable(00_application
    "00_application.cpp"
)

target_link_libraries(00_application PRIVATE engine)