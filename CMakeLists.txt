cmake_minimum_required(VERSION 3.12)
project(game_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(game_cpp main.cpp)

find_package(SDL2 REQUIRED)