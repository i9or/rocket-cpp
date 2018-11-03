cmake_minimum_required(VERSION 3.10)

file(GLOB CHAPTER2_ASSETS assets/*)
file(COPY ${CHAPTER2_ASSETS} DESTINATION assets/)

include_directories("./src")
include_directories(${SDL2_INCLUDE_DIR})

file (GLOB CHAPTER2_SOURCES src/*.cpp)
file (GLOB CHAPTER2_HEADERS src/*.h)

add_executable(chapter2 ${CHAPTER2_SOURCES} ${CHAPTER2_HEADERS} ${CHAPTER2_ASSETS})

target_link_libraries(chapter2 ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_MIXER_LIBRARY})
