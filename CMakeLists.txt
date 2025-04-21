cmake_minimum_required(VERSION 3.10)
project(journal-c99 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# from clay github.com/nicbarker/clay
# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "c1ab645ca298a2801097931d1079b10ff7eb9df8"
    GIT_PROGRESS TRUE
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(raylib)

message(STATUS "raylib downloaded to: ${raylib_SOURCE_DIR}")

include_directories(include)
include_directories(graph)


file(GLOB SOURCES "src/*.c")
file(GLOB GSOURCES "graph/*.c")

add_executable(journal-c99 ${SOURCES})

target_compile_definitions(journal-c99 PRIVATE RAYGUI_IMPLEMENTATION)
target_link_libraries(journal-c99 raylib)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GRAPHVIZ REQUIRED libgvc)

# Include directories for Graphviz headers
include_directories(${GRAPHVIZ_INCLUDE_DIRS})
link_directories(${GRAPHVIZ_LIBRARY_DIRS})

# Add the source file for your project
add_executable(ggen graph/gen_graph.c src/utils.c)

# Link Graphviz libraries
target_link_libraries(ggen PRIVATE raylib  ${GRAPHVIZ_LIBRARIES})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

#message(STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

# Configuración específica para debug, "d" minúscula
# cmake -DCMAKE_BUILD_TYPE=debug ..
if (CMAKE_BUILD_TYPE STREQUAL "debug")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} \
    -std=c99 \
    -g3      \
    -Wall    \
    -Werror  \
    -Wconversion \
    -Wdouble-promotion \
    -fsanitize=address,undefined \
    -Wno-unused-parameter \
    -Wno-unused-function \
    -Wno-sign-conversion")

  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}  \
    -std=c99 \
    -g3      \
    -Wall    \
    -Werror  \
    -Wconversion \
    -Wdouble-promotion \
    -fsanitize=address,undefined \
    -Wno-unused-parameter \
    -Wno-unused-function \
    -Wno-sign-conversion")
endif()

