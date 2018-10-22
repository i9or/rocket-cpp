cmake_minimum_required(VERSION 3.12)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(chapter1 main.cpp Game.cpp Game.h)

target_link_libraries(chapter1 ${SDL2_LIBRARY})
