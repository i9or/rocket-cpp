cmake_minimum_required(VERSION 3.12)
project(chapter2)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})