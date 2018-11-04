cmake_minimum_required(VERSION 3.10)
project(rocket-cpp)

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
    message(STATUS "\tInclude path: ${SDL2_INCLUDE_DIR}")
    message(STATUS "\tLibrary path: ${SDL2_LIBRARY}")
endif ()

if (!${SDL2_IMAGE_FOUND})
    message(STATUS "SDL2_image component was not found...")
else ()
    message(STATUS "SDL2_image component was found!")
    message(STATUS "\tInclude path: ${SDL2_IMAGE_INCLUDE_DIR}")
    message(STATUS "\tLibrary path: ${SDL2_IMAGE_LIBRARY}")
endif ()

if (!${SDL2_MIXER_FOUND})
    message(STATUS "SDL2_mixer component was not found...")
else ()
    message(STATUS "SDL2_mixer component was found!")
    message(STATUS "\tInclude path: ${SDL2_MIXER_INCLUDE_DIR}")
    message(STATUS "\tLibrary path: ${SDL2_MIXER_LIBRARY}")
endif ()

if (!${SDL2_TTF_FOUND})
    message(STATUS "SDL2_ttf component was not found...")
else ()
    message(STATUS "SDL2_ttf component was found!")
    message(STATUS "\tInclude path: ${SDL2_TTF_INCLUDE_DIR}")
    message(STATUS "\tLibrary path: ${SDL2_TTF_LIBRARY}")
endif ()

file(GLOB ROCKET_CPP_ASSETS assets/*)
file(COPY ${ROCKET_CPP_ASSETS} DESTINATION assets/)

include_directories("./src")
include_directories(${SDL2_INCLUDE_DIR})

file (GLOB ROCKET_CPP_SOURCES src/*.cpp)
file (GLOB ROCKET_CPP_HEADERS src/*.h)

add_executable(${PROJECT_NAME} ${ROCKET_CPP_SOURCES} ${ROCKET_CPP_HEADERS} ${ROCKET_CPP_ASSETS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${SDL2_MIXER_LIBRARY})
