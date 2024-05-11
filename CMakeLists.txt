include(FetchContent)

cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_REQUIRED ON)

project(RTetris)

set(SFML_VERSION 2.5.1)
set(IMGUI_VERSION 1.90)

# SFML Fetch
message("-- Fetching SFML, ImGui and ImGui-SFML libraries")

FetchContent_Declare(
        sfml
        URL "https://github.com/SFML/SFML/archive/${SFML_VERSION}.zip"
)
FetchContent_Declare(
        imgui
        URL "https://github.com/ocornut/imgui/archive/v${IMGUI_VERSION}.zip"
)
FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY "https://github.com/SFML/imgui-sfml.git"
        GIT_TAG "2.6.x"
)

option(SFML_BUILD_NETWORK "Build network" OFF)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/build/_deps/imgui-src)
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
FetchContent_MakeAvailable(sfml imgui imgui-sfml)

message("-- Fetching SFML, ImGui and ImGui-SFML libraries - done")

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
        ImGui-SFML::ImGui-SFML
)
message("-- Linking external libraries - done")

message("-- Including headers directories")
target_include_directories(RTetris PUBLIC include)
message("-- Including headers directories - done")