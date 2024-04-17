cmake_minimum_required(VERSION 3.22)
project(RTetris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_REQUIRED ON)

# SFML Fetch
message("-- Fetching SFML library")
include(FetchContent)
FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "2.5.1"
    GIT_PROGRESS ON
)
FetchContent_MakeAvailable(sfml)
message("-- Fetching SFML library - done")

message("-- Copying assets to the build")
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
message("-- Copying assets to the build - done")

message("-- Adding source files to build")
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(RTetris ${SOURCES})
message("-- Adding source files to build - done")
target_compile_options(RTetris PRIVATE -Wall -Wextra -pedantic)

message("-- Linking external libraries")
target_link_libraries(RTetris
    PUBLIC
    sfml-audio
    sfml-graphics
    sfml-window
    sfml-system
)
message("-- Linking external libraries - done")

message("-- Including headers directories")
target_include_directories(RTetris PUBLIC include)
message("-- Including headers directories - done")