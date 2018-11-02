cmake_minimum_required(VERSION 3.12)

project(game-cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

if (!${SDL2_FOUND})
    message(STATUS "SDL2 was not found...")
else ()
    message(STATUS "SDL2 was found!")
    message(STATUS "Include dirs: ${SDL2_INCLUDE_DIR}")
    message(STATUS "Library dirs: ${SDL2_LIBRARY}")
endif ()

if (!${SDL2_IMAGE_FOUND})
    message(STATUS "SDL2_image component was not found...")
else ()
    message(STATUS "SDL2_image component was found! Version: ${SDL2_IMAGE_VERSION_STRING}")
endif ()

if (!${SDL2_MIXER_FOUND})
    message(STATUS "SDL2_mixer component was not found...")
else ()
    message(STATUS "SDL2_mixer component was found! Version: ${SDL2_MIXER_VERSION_STRING}")
endif ()

if (!${SDL2_TTF_FOUND})
    message(STATUS "SDL2_ttf component was not found...")
else ()
    message(STATUS "SDL2_ttf component was found! Version: ${SDL2_TTF_VERSION_STRING}")
endif ()

add_subdirectory(chapter1)
add_subdirectory(chapter2)
