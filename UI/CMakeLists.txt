cmake_minimum_required(VERSION 3.22)
include(FetchContent)

project(UI)

# SFML Fetch
FetchContent_Declare(
    sfml
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "2.5.1"
    GIT_PROGRESS ON
)
FetchContent_MakeAvailable(sfml)

link_libraries(
    sfml-audio
    sfml-graphics
    sfml-system
    sfml-window
)

# find_library(SFML sfml REQUIRED)
add_library(UI SHARED DebugInfo.cpp DebugInfo.h)