cmake_minimum_required(VERSION 3.10)
project(journal-c99 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)
file(GLOB SOURCES "src/*.c")

find_package(raylib REQUIRED)
add_executable(journal-c99 ${SOURCES})

target_compile_definitions(journal-c99 PRIVATE RAYGUI_IMPLEMENTATION)
target_link_libraries(journal-c99 raylib)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}\
    -std=c99 \
    -Wall    \
    -Werror  \
    -Wconversion \
    -Wdouble-promotion \
    -Wno-sign-conversion")


