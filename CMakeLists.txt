cmake_minimum_required(VERSION 4.0)

# TODO: Use more appropriate name
project(game)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
# set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

option(GAME_HOT_RELOAD "Build game with hot reload support" OFF)

if(GAME_HOT_RELOAD)
    if(NOT WIN32)
        set(BUILD_SHARED_LIBS ON)
    endif()
endif()

add_subdirectory(./external/)
add_subdirectory(./src/)
