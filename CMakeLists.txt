cmake_minimum_required(VERSION 3.10)
project(journal-c99 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find_package(raylib REQUIRED)
# from clay github.com/nicbarker/clay
# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib)

include_directories(include)
file(GLOB SOURCES "src/*.c")

add_executable(journal-c99 ${SOURCES})

target_compile_definitions(journal-c99 PRIVATE RAYGUI_IMPLEMENTATION)
target_link_libraries(journal-c99 raylib)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}\
    -std=c99 \
    -g3     \
    -Wall    \
    -Werror  \
    -Wconversion \
    -fsanitize=address,undefined \
    -Wdouble-promotion \
    -Wno-sign-conversion")


