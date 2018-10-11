cmake_minimum_required(VERSION 3.12)
project(multi-pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 COMPONENTS main image mixer ttf)
include_directories(${SDL2_INCLUDE_DIR})

add_executable(${CMAKE_PROJECT_NAME} main.cpp Game.cpp Game.h)

target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARIES})