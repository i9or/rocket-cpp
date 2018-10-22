cmake_minimum_required(VERSION 3.12)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(chapter2 main.cpp)

target_link_libraries(chapter2 ${SDL2_LIBRARY})
